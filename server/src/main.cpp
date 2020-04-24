#include "../includes/Server.hpp"

void	*player_manager(void *ptr)
{
	Server	*serv;
	int		t;
	int		last_tick;
	int		last_backup;

	serv = (Server *)ptr;
	t = time(NULL);
	srand(t);
	last_tick = t;
	last_backup = t;
	std::cout << "managin players\n";
	while (1)
	{
		for (std::map<std::string, Player *>::iterator it = serv->players.begin(); it != serv->players.end(); ++it)
		{
			int ret = it->second->tick(serv);
			if (ret == 2 && it->second->fd > 0)
				serv->awardKill(it->second);
			else if (ret == 3)
				serv->notify(it->second, std::string("You have died and lost half of your total experience."));
			if (FD_ISSET(it->second->fd, &serv->active_fd_set) && serv->sendStatus(it->second) <= 0)
			{
				printf("REMOVING PLAYER\n");
				serv->removePlayer(it->second);
				FD_CLR(it->second->fd, &serv->active_fd_set);
				close(it->second->fd);
				printf("DONE\n");
			}
		}
		int cur;
		while ((cur = (int)time(NULL)) == last_tick)
			usleep(25);
		if (cur - last_backup >= 30)
		{
			last_backup = cur;
			serv->sqlBackup();
		}
		last_tick++;
	}
	printf("exit man\n");
}

int		loop(void)
{
	Server 				serv;
	struct sockaddr_in	clientname;
	socklen_t				size;
	int					i;
	int					x = 0;
	int					ret;
	pthread_t			player_thread;

	pthread_create(&player_thread, NULL, player_manager, &serv);
	while (1)
	{
		x++;
		FD_ZERO(&serv.active_fd_set);
		FD_SET(serv.sock, &serv.active_fd_set);
		for (std::map<std::string, Player *>::iterator it = serv.players.begin(); it != serv.players.end(); ++it)
		{
			if (it->second->fd > 0)
				FD_SET(it->second->fd, &serv.active_fd_set);
		}
		if ((ret = select(FD_SETSIZE, &serv.active_fd_set, NULL, NULL, NULL)) < 0)
		{
			perror("select");
			exit(-1);
		}
		printf("%d %d\n", x, ret);
		for (i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &serv.active_fd_set))
			{
				if (i == serv.sock)
				{
					int new_sock;
					printf("here sock conn\n");
					size = sizeof(clientname);
					new_sock = accept(serv.sock, (struct sockaddr*)&clientname, &size);
					FD_SET(new_sock, &serv.active_fd_set);
					printf("new conn\n");
				}
				else
				{
					t_packet	pack;
					int		nbytes;
					printf("here data\n");
					nbytes = read(i, &pack, sizeof(t_packet));
					printf("%d | %zu\n", nbytes, sizeof(t_packet));
					if (nbytes <= 0)
					{
						printf("err\n");
						close(i);
						FD_CLR(i, &serv.active_fd_set);
						for (std::map<std::string, Player *>::iterator it = serv.players.begin(); it != serv.players.end(); ++it)
							if (it->second->fd == i)
								serv.removePlayer(it->second);
					}
					else if (serv.playerExists(&pack))
					{
						if (serv.processPacket(&pack, i) == -1)
						{
							close(i);
							FD_CLR(i, &serv.active_fd_set);
							FD_CLR(i, &serv.read_fd_set);
							printf("login denied\n");
						}
						else
						{
							printf("COMMAND: %s\n", pack.command);
							printf("DATA: ");
							for (int i = 0; pack.data[i] && i < 14 && strlen(pack.data[i]) > 0; i++)
								printf("%s", pack.data[i]);
							printf("\n");
							fflush(0);
						}
					}
					else
					{
						printf("here new\n");
						serv.newPlayer(&pack, i);
					}
				}
			}
		}
	}
	printf("exit loop\n");
}

int		main(void)
{
	loop();
}
