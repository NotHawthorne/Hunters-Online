#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <map>
# include <pthread.h>
# include <ctime>
# include <time.h>
# include <sqlite3.h>
# include <signal.h>
# include <locale>
# include "player.h"
# include "packet.h"
# include "utils.h"
# include "effect.h"
# include "item.h"

# define PORT 4242
# define MAXMSG 512

# define REGISTER "reg"
# define DB_PATH "./db/users.db"
# define SQL_FIND_USER(user) std::string(std::string("SELECT * from users WHERE name=\"") + std::string(user) + std::string("\";")).c_str()

class	Server {
public:
	Server();
	~Server();
	int		playerExists(t_packet *pack);
	int		newPlayer(t_packet *pack, int nfd);
	int		processPacket(t_packet *pack, int nfd);
	int		sendStatus(Player *p);
	int		removePlayer(Player *p);
	int		sendChat(t_packet *p);
	int		sqlBackup();
	int		loadPlayers();
	int		loginRequest(t_packet *p);
	int		awardKill(Player *p);
	int		notify(Player *p, std::string str);
	int		sendItemList(Player *p, std::map<int, Item *> *list, int type);
	int		loadBases();
	int		loadAuras();
	Item	*genItem(int level);
	int		grantItem(Player *p, Item *i);
	int		loadInventories();
	int		loadInstances();

	int								sock;
	fd_set							active_fd_set;
	fd_set							read_fd_set;
	std::map<std::string, Player *>	players;
	std::map<int, Item *>			items;
	std::map<int, ItemBase *>		item_bases;
	std::map<int, Aura *>			auras;
	struct sockaddr_in				servaddr;
	sqlite3							*db;
};

#endif