#ifndef CLIENT_H
# define CLIENT_H

#include <arpa/inet.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <sqlite3.h>
#include <map>
#include "effect.h"
#include "item.h"
#include "window.h"
#include "packet.h"

#define ADDRESS "127.0.0.1"
#define PORT 4242

namespace CurseWar
{
	class	Client
	{
	public:
		Client(char *user, char *pass);
		~Client();
		int	sendPacket(char *id, char *command, char **data);
		int	sendChat(char *msg, size_t len, bool whisper, char *dst);
		int	initDB();
		void	recvItemList(std::map<int, Item *> *l, t_packet *h);

		sqlite3					*db;
		std::map<int, Item *>	inventory;
		std::map<int, Item *>	equipment;
		std::map<int, ItemBase *>	item_base;
		std::map<int, Aura *>		auras;
		bool				eq_empty;
		bool				inven_empty;
		int					conn_fd;
		struct sockaddr_in	server_addr;
		char				name[16];
		int					gold;
		int					hunters;
		
	};
}

typedef struct	s_thread_data
{
	CurseWar::Client	*cli;
	CurseWar::Screen	*scr;
}				t_thread_data;

int		unpad(char *str);

#endif
