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

#define ADDRESS "64.225.45.59"
#define _ADDRESS "127.0.0.1"
#define PORT 4242

enum display_states
{
	WELCOME,
	HOME,
	INVENTORY,
	EQUIPMENT,
	INSPECT,
	EINSPECT,
	PLAYERS
};

class Player {
public:
	char	name[16];
	int		level;
	Player(t_packet *p);
};

namespace HeroShell
{
	class	Client
	{
	public:
		Client();
		~Client();
		int	sendPacket(char *id, char *command, char **data);
		int	sendChat(char *msg, size_t len, bool whisper, char *dst);
		int	initDB();
		void	recvItemList(std::map<int, Item *> *l, t_packet *h);
		int	updateDisplay(WINDOW *win, int new_state);
		void	recvUserList(std::map<int, Player *> *l, t_packet *h);

		sqlite3					*db;
		std::map<int, Item *>	inventory;
		std::map<int, Item *>	equipment;
		std::map<int, ItemBase *>	item_base;
		std::map<int, Aura *>		auras;
		std::map<int, Player *>		plist;
		int					state;
		int					last_state;
		bool				eq_empty;
		bool				inven_empty;
		int					inven_page;
		int					inspect_slot;
		int					player_page;
		int					conn_fd;
		struct sockaddr_in	server_addr;
		char				name[16];
		int					gold;
		int					hunters;
		int					gold_exponent;
	};
}

typedef struct	s_thread_data
{
	HeroShell::Client	*cli;
	HeroShell::Screen	*scr;
}				t_thread_data;

int		unpad(char *str);

#endif
