#include "../../includes/window.h"
#include "../../includes/client.h"
#include "../../includes/login.h"

# define DEBUG 0

extern HeroShell::Screen *mainscr;

int		unpad(char *str)
{
	int last = 0;
	for (int i = 0; str[i] && i < strlen(str); i++)
		if (str[i] && str[i] != ' ')
			last = i;
	return (last + 1);
}

void	listen_to_server(t_thread_data *d, std::string command)
{
	if (command.length() < 9)
		return ;
	if (strncmp(command.c_str(), "You deal ", 9) == 0)
	{
		int damage = std::atoi(command.c_str() + 9);
		d->plr->add_data(DAMAGE, damage);
	}
}

void	*listener(void *ptr)
{
	t_thread_data	*d = (t_thread_data*)ptr;
	t_packet		*p;
	char			data[sizeof(t_packet)];

	while (1)
	{
		int	tmp;
		int	rbytes = read(d->cli->conn_fd, data, sizeof(t_packet));
		while (rbytes > 0 && rbytes < sizeof(t_packet))
		{
			tmp = read(d->cli->conn_fd, data + rbytes, sizeof(t_packet) - rbytes);
			if (tmp > 0)
				rbytes += tmp;
		}
		p = (t_packet *)&data;
		if (rbytes > 0)
		{
			if (DEBUG == 1)
				wprintw(d->scr->log, "recieved: %s\n", p->command);
			if (strcmp(p->command, "STATUS") == 0)
				d->scr->update(d->plr, p);
			else if (strcmp(p->command, "CHAT") == 0 ||
						strcmp(p->command, "NOTIFY") == 0)
			{
				std::string		st("");
				int a = atoi(p->data[0]);
				int res = strcmp(p->command, "NOTIFY");
				int level = atoi(p->data[1]);
				for (int i = 2; i < 30 && st.size() < a; i++)
					st += std::string(p->data[i]);
				if (strcmp(p->id, "SERVER") == 0)
				{
					listen_to_server(d, st);
					wattron(d->scr->log, COLOR_PAIR(res ? 1 : 3));
					wprintw(d->scr->log, "%s\n", st.c_str());
					wattron(d->scr->log, COLOR_PAIR(1));
					wrefresh(d->scr->log);
				}
				else
				{
					wattron(d->scr->chat, COLOR_PAIR(res ? 1 : 3));
					wprintw(d->scr->chat, "%s: %s\n", p->id, st.c_str());
					wattron(d->scr->chat, COLOR_PAIR(1));
					wrefresh(d->scr->chat);
				}
			}
			else if (strcmp(p->command, "PLIST_HEAD") == 0)
			{
				d->cli->plist.clear();
				d->cli->recvUserList(&d->cli->plist, p);
				d->cli->last_state = -1;
				d->cli->state = PLAYERS;
				d->cli->updateDisplay(d->scr->display, PLAYERS);
			}
			else if (strcmp(p->command, "ILIST_HEAD") == 0)
			{
				switch (atoi(p->data[1]))
				{
					case 0:
						d->cli->inventory.clear();
						d->cli->recvItemList(&d->cli->inventory, p);
						if (d->cli->state != INVENTORY)
							break ;
						d->cli->last_state = -1;
						d->cli->updateDisplay(d->scr->display, INVENTORY);
						break ;
					case 1:
						d->cli->equipment.clear();
						d->cli->recvItemList(&d->cli->equipment, p);
						break ;
					default:
						std::map<int, Item *> m;
						d->cli->recvItemList(&m, p);
						printf("recieved %d items, dunno where they go tho so\n", atoi(p->data[0]));
						printf("opcode %d\n", atoi(p->data[1]));
						break ;
				}
			}
			else if (strcmp(p->command, "WHIS") == 0)
			{
				std::string	msg(p->data[2]);
				for (int i = 3; p->data[i][0]; i++)
					msg += std::string(p->data[i]);
				wattron(d->scr->chat, COLOR_PAIR(2));
				wprintw(d->scr->chat, "%s %s: %s\n",
						strcmp(p->id, d->cli->name) ? "from" : "to",
						strcmp(p->id, d->cli->name) ? p->id : p->data[0], msg.c_str());
				wattron(d->scr->chat, COLOR_PAIR(1));
				wrefresh(d->scr->chat);
			}
			else
				wprintw(d->scr->log, "Unhandled msg: %s by %s\n", p->id, p->command);
		}
		d->cli->updateDisplay(d->scr->display, d->cli->state);
		usleep(50);
	}
	return (NULL);
}

int		parse(char *str, HeroShell::Client *cli, HeroShell::Screen *scr)
{
	std::string	s(str);
	std::vector<std::string> tokens;
	std::istringstream checkl(s);
	std::string	inter;
	std::locale loc;
	char	**data = new char*[30];
	int x = 0;

	while (getline(checkl, inter, ' '))
		tokens.push_back(inter);
	std::string cmd = tokens[0];
	if (cmd.compare(std::string("buy")) == 0)
	{
		if (tokens.size() <= 2)
			return (0);
		std::string amt = tokens[1];
		std::string	type = tokens[2];
		if (type.compare("hunter") == 0 ||
				type.compare("hunters") == 0)
		{
			data[0] = new char[16];
			bzero(data[0], 16);
			data[1] = NULL;
			memcpy(data[0], amt.c_str(), amt.size() > 16 ? 15 : amt.size());
			data[0][amt.size() > 16 ? 15 : amt.size()] = 0;
			cli->sendPacket(cli->name, "BUY_HUNTER", data);
			return (1);
		}
	}
	else if (cmd.compare(std::string("view")) == 0)
	{
		if (tokens.size() <= 1)
			return (0);
		std::string	desire = tokens[1];
		if (desire.compare("inventory") == 0)
		{
			cli->state = INVENTORY;
			cli->updateDisplay(scr->display, INVENTORY);
			for (std::map<int, Item *>::iterator it = cli->inventory.begin(); it != cli->inventory.end(); ++it)
			{
				wprintw(scr->log, "%d - %s\n", x, cli->item_base[it->second->base_id]->name);
				++x;
			}
			wrefresh(scr->log);
			return (1);
		}
		else if (desire.compare("equipment") == 0)
		{
			if (cli->equipment.size() < 1)
			{
				wprintw(scr->log, "No equipment! Try to <equip> something first.\n");
				wrefresh(scr->log);
				return (1);
			}

			cli->state = EQUIPMENT;
			cli->updateDisplay(scr->display, EQUIPMENT);
			for (std::map<int, Item *>::iterator it_eq = cli->equipment.begin(); \
				it_eq != cli->equipment.end(); it_eq++)
			{
				wprintw(scr->log, "%d - %s\n", x, cli->item_base[it_eq->second->base_id]->name);
				++x;
			}
			wrefresh(scr->log);
			return (1);
		}
		else if (desire.compare("home") == 0)
		{
			cli->state = WELCOME;
			cli->updateDisplay(scr->display, cli->state);
			wrefresh(scr->display);
			return (1);
		}
	}
	else if (cmd.compare(std::string("whisper")) == 0 ||
				cmd.compare(std::string("tell")) == 0 ||
				cmd.compare(std::string("message")) == 0 ||
				cmd.compare(std::string("pm")) == 0)
	{
		if (tokens.size() <= 3)
			return (0);
		std::string	dest(tokens[1]);
		std::string	msg(tokens[2]);
		for (int i = 3; i < tokens.size(); i++)
			msg = msg + " " + tokens[i];
		cli->sendChat((char*)msg.c_str(), msg.size(), 1, (char*)dest.c_str());
		return (1);
	}
	else if (cmd.compare(std::string("page")) == 0)
	{
		if (tokens.size() < 2)
			return (0);
		int des = std::atoi(tokens[1].c_str());
		if ((des - 1) >= 0)
		{
			cli->inven_page = std::atoi(tokens[1].c_str()) - 1;
			if (cli->state == INVENTORY)
				cli->last_state = -1;
			cli->updateDisplay(scr->display, cli->state);
		}
		return (1);
	}
	else if (cmd.compare(std::string("inspect")) == 0)
	{
		if (tokens.size() < 2)
			return (0);
		cli->inspect_slot = std::atoi(tokens[1].c_str());
		cli->last_state = -1;
		cli->state = INSPECT;
		cli->updateDisplay(scr->display, INSPECT);
		return (1);
	}
	else if (cmd.compare(std::string("einspect")) == 0)
	{
		if (tokens.size() < 2)
			return (0);
		cli->inspect_slot = std::atoi(tokens[1].c_str());
		cli->last_state = -1;
		cli->state = EINSPECT;
		cli->updateDisplay(scr->display, EINSPECT);
		return (1);
	}
	else if (cmd.compare(std::string("drop")) == 0)
	{
		wprintw(scr->log, "You tried to set it down, but as soon as you turned around you found it in your hand again.\n");
		return (1);
	}
	else if (cmd.compare(std::string("equip")) == 0)
	{
		t_packet	np;
		bzero(np.id, 16);
		bzero(np.command, 16);
		bzero(np.data[0], 16);
		bzero(np.data[1], 16);
		memcpy(np.id, cli->name, strlen(cli->name));
		memcpy(np.command, "EQUIP", 5);
		int slot = -1;
		if (tokens.size() < 2)
		{
			if (cli->state == INSPECT)
				slot = cli->inspect_slot;
			else
				return (1);
		}
		else
		{
			slot = std::stoi(tokens[1]);
		}
		if (slot < 0 || slot >= cli->inventory.size())
			return (1);
		std::string	des = std::to_string(cli->inventory[slot]->instance_id);
		memcpy(np.data[0], des.c_str(), des.size());
		write(cli->conn_fd, &np, sizeof(t_packet));
		return (1);
	}
	else if (cmd.compare(std::string("help")) == 0)
	{
		if (tokens.size() >= 2 && tokens[1].size() > 0)
		{
			if (tokens[1].compare(std::string("inspect")) == 0)
				wprintw(scr->log, "inspect [inventory_number]\n");
			else if (tokens[1].compare(std::string("page")) == 0)
				wprintw(scr->log, "page [inventory_page_number]\n");
			else if (tokens[1].compare(std::string("whisper")) == 0 ||
						tokens[1].compare(std::string("tell")) == 0 ||
						tokens[1].compare(std::string("message")) == 0 ||
						tokens[1].compare(std::string("pm")) == 0)
				wprintw(scr->log, "%s [recipient_username] {msg}\n", tokens[1].c_str());
			else if (tokens[1].compare(std::string("view")) == 0)
				wprintw(scr->log, "view [inventory/equipment/home]\n");
			else if (tokens[1].compare(std::string("buy")) == 0)
				wprintw(scr->log, "buy [number] hunter(s)\n");
			else
				wprintw(scr->log, "no help available for %s\n", tokens[1].c_str());
		}
		else
			wprintw(scr->log, "available commands:\nbuy, inspect, message [pm/tell/whisper], view\n"); 
		wrefresh(scr->log);
		return (1);
	}
	else if (cmd.compare(std::string("players")) == 0)
	{
		t_packet	np;

		bzero(np.id, 16);
		bzero(np.command, 16);
		bzero(np.data[0], 16);
		bzero(np.data[1], 16);
		memcpy(np.command, "REQ_PLAYERS", 11);
		memcpy(np.id, cli->name, strlen(cli->name));
		memcpy(np.data[0], std::to_string(((LINES * 0.75) - 3) * cli->player_page).c_str(), std::to_string(((LINES * 0.75) - 3) * cli->player_page).size());
		write(cli->conn_fd, &np, sizeof(t_packet));
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	bool				valid = false;
	LoginManager		*m = new LoginManager();
	HeroShell::Client	*cli = NULL;
	while (valid != true)
	{
		if (cli)
			delete cli;
		cli = new HeroShell::Client();
		bzero(cli->name, 16);
		if (m->readInput() > 0 && cli->conn_fd >= 0)
		{
			char	*us = field_buffer(m->fields[0], 0);
			us[unpad(us)] = 0;
			char	*pw = (char*)m->pass.c_str();
			memcpy(cli->name, us, strlen(us));
			if (m->attemptLogin(cli->conn_fd, us, pw) > 0)
				break ;
		}
		else if (cli->conn_fd < 0)
			mvwprintw(m->mainwin, 6, 1, "server dead! :(    ");
	}
	HeroShell::Screen	scr;
	HeroShell::PlayerAvg	plr;
	t_thread_data		d;
	char				*buf;
	pthread_t			listenthread;
	int	i = 0;

	mainscr = &scr;
	buf = NULL;
	d.cli = cli;
	d.scr = &scr;
	d.plr = &plr;
	pthread_create(&listenthread, NULL, listener, &d);
	while (1)
	{
		int c = wgetch(scr.console);
		if (c == '\033')
		{
			wgetch(scr.console);
			switch (wgetch(scr.console))
			{
				case 'D':
					form_driver(scr.form, REQ_PREV_CHAR);
					break ;
				case 'C':
					form_driver(scr.form, REQ_NEXT_CHAR);
					break ;
				case KEY_BACKSPACE:
					form_driver(scr.form, REQ_DEL_CHAR);
					break ;
				default:
					break ;
			}
		}
		else
		{
			switch(c)
			{
				case 4:
					return (0);
					break ;
				case 127:
					buf = field_buffer(scr.input[0], 0);
					if (strlen(buf) > 1)
						form_driver(scr.form, REQ_DEL_PREV);
					break ;
				case 10:
					form_driver(scr.form, REQ_VALIDATION);
					buf = field_buffer(scr.input[0], 0) + 1;
					buf[unpad(buf)] = 0;
					if (strncmp(buf, "exit", 4) == 0)
					{
						close(cli->conn_fd);
						exit(0);
					}
					//mvwprintw(scr.console, 1, 1, buf);
					else if (!parse(buf, cli, &scr))
						if (cli->sendChat(buf, (size_t)unpad(buf), 0, NULL) == 0)
							mvwprintw(scr.console, 1, 1, "ERR              ");
					set_field_buffer(scr.input[0], 0, "");
					form_driver(scr.form, '>');
					break ;
				default:
					form_driver(scr.form, c);
					break ;
			}
		}
		//wrefresh(scr.display);
		wrefresh(scr.console);
		//wrefresh(scr.info);
		i++;
	}
}
