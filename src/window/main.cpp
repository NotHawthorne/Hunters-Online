#include "../../includes/window.h"
#include "../../includes/client.h"

extern CurseWar::Screen *mainscr;

int		unpad(char *str)
{
	int last = 0;
	for (int i = 0; str[i] && i < strlen(str); i++)
		if (str[i] && str[i] != ' ')
			last = i;
	return (last + 1);
}

void	*listener(void *ptr)
{
	t_thread_data	*d = (t_thread_data*)ptr;
	t_packet		p;

	while (1)
	{
		if (read(d->cli->conn_fd, &p, sizeof(t_packet)) > 0)
		{
			if (strcmp(p.command, "STATUS") == 0)
				d->scr->update(&p);
			else if (strcmp(p.command, "CHAT") == 0 ||
						strcmp(p.command, "NOTIFY") == 0)
			{
				std::string		st("");
				int a = atoi(p.data[0]);
				for (int i = 1; i < 30 && st.size() < a; i++)
					st += std::string(p.data[i]);
				wprintw(d->scr->log, "%s: %s\n", p.id, st.c_str());
				wrefresh(d->scr->log);
			}
			else if (strcmp(p.command, "ILIST_HEAD") == 0)
			{
				switch (atoi(p.data[1]))
				{
					case 0:
						d->cli->inventory.clear();
						d->cli->recvItemList(&d->cli->inventory, &p);
						if (d->cli->state != INVENTORY)
							break ;
						d->cli->last_state = -1;
						d->cli->updateDisplay(d->scr->display_port, INVENTORY);
						break ;
					case 1:
						d->cli->equipment.clear();
						d->cli->recvItemList(&d->cli->equipment, &p);
						break ;
					default:
						std::map<int, Item *> m;
						d->cli->recvItemList(&m, &p);
						printf("recieved %d items, dunno where they go tho so\n", atoi(p.data[0]));
						printf("opcode %d\n", atoi(p.data[1]));
						break ;
				}
			}
			else if (strcmp(p.command, "WHIS") == 0)
			{
				std::string	msg(p.data[2]);
				for (int i = 3; p.data[i][0]; i++)
					msg += std::string(p.data[i]);
				wattron(d->scr->log, COLOR_PAIR(2));
				wprintw(d->scr->log, "%s %s: %s\n",
						strcmp(p.id, d->cli->name) ? "from" : "to",
						strcmp(p.id, d->cli->name) ? p.id : p.data[0], msg.c_str());
				wattron(d->scr->log, COLOR_PAIR(1));
				wrefresh(d->scr->log);
			}
			else
				printf("err\n");
		}
		d->cli->updateDisplay(d->scr->display_port, d->cli->state);
		usleep(50);
	}
	return (NULL);
}

int		parse(char *str, CurseWar::Client *cli, CurseWar::Screen *scr)
{
	std::string	s(str);
	std::vector<std::string> tokens;
	std::istringstream checkl(s);
	std::string	inter;
	std::locale loc;
	char	**data = new char*[30];

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
	if (cmd.compare(std::string("view")) == 0)
	{
		if (tokens.size() <= 1)
			return (0);
		std::string	desire = tokens[1];
		if (desire.compare("inventory") == 0)
		{
			cli->state = INVENTORY;
			cli->updateDisplay(scr->display_port, INVENTORY);
			for (std::map<int, Item *>::iterator it = cli->inventory.begin(); it != cli->inventory.end(); ++it)
				wprintw(scr->log, "%s\n", cli->item_base[it->second->base_id]->name);
			wrefresh(scr->log);
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
		//wattron(scr->log, COLOR_PAIR(2));
		//wprintw(scr->log, "to %s: %s\n", dest.c_str(), msg.c_str());
		//wattron(scr->log, COLOR_PAIR(1));
		//wrefresh(scr->log);
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
			cli->last_state = -1;
			cli->updateDisplay(scr->display_port, cli->state);
		}
		return (1);
	}
	else if (cmd.compare(std::string("inspect")) == 0)
	{
		if (tokens.size() < 2)
			return (0);
		cli->inspect_slot = std::atoi(tokens[1].c_str());
		cli->last_state = -1;
		cli->updateDisplay(scr->display_port, INSPECT);
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc != 3)
		return (printf("usage: ./cursewar [user] [pass]\n"));
	CurseWar::Client	cli(argv[1], argv[2]);
	CurseWar::Screen	scr;
	t_thread_data		d;
	char				*buf;
	pthread_t			listenthread;
	int	i = 0;

	mainscr = &scr;
	buf = NULL;
	d.cli = &cli;
	d.scr = &scr;
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
					if (strncmp(buf, "exit", 4) == 0)
					{
						close(cli.conn_fd);
						exit(0);
					}
					//mvwprintw(scr.console, 1, 1, buf);
					else if (!parse(buf, &cli, &scr))
						if (cli.sendChat(buf, (size_t)unpad(buf), 0, NULL) == 0)
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
