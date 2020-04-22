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
			else
				printf("err\n");
		}
		usleep(50);
	}
	return (NULL);
}

int		parse(char *str, CurseWar::Client *cli)
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
					else if (!parse(buf, &cli))
						if (cli.sendChat(buf, (size_t)unpad(buf)) == 0)
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
