#include "../includes/Server.hpp"
#include "../includes/utils.h"

Server::Server()
{
	//int	f = 1;
	int	rc;

	signal(SIGPIPE, SIG_IGN);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	//setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &f, sizeof(int));
	bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if (listen(sock, 10) < 0)
	{
		perror("listen\n");
		exit(-1);
	}
	FD_ZERO(&active_fd_set);
	FD_SET(sock, &active_fd_set);
	std::cout << "Initialized.\n";
	std::cout << "Loading db...\n";
	rc = sqlite3_open(DB_PATH, &db);
	if (rc)
		std::cout << "DB init failed: " << rc << std::endl;
	else
		std::cout << "DB init succeeded.\n";
	std::cout << "Loading players...\n";
	loadPlayers();
	std::cout << "Loaded " << players.size() << " players!\n";
	std::cout << "Loading item bases...\n";
	loadBases();
	std::cout << "Loaded " << item_bases.size() << " bases!\n";
	std::cout << "Loading auras...\n";
	loadAuras();
	std::cout << "Loaded " << auras.size() << " auras!\n";
}

int	Server::notify(Player *p, std::string info)
{
	t_packet	pa;
	const char	*d;
	int			x = 1;
	std::string	s = std::to_string(info.size());

	memcpy(pa.id, "SERVER\0", 7);
	memcpy(pa.command, "NOTIFY\0", 7);
	d = info.c_str();
	memcpy(pa.data[0], s.c_str(), s.size() + 1);
	for (int i = 0; i < (int)info.size(); i+= 15)
	{
		bzero(pa.data[x], 16);
		memcpy(pa.data[x++], d + i, info.size() - i > 15 ? 15 : info.size() - i);
	}
	write(p->fd, &pa, sizeof(t_packet));
	return (1);
}

/*static int	generic_sql_callback(void *ret, int argc, char **argv, char **colNames)
{
	int	*r = (int*)ret;

	
	r = 1;
}*/

int	Server::sqlBackup()
{
	std::string	q("");
	for (std::map<std::string, Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		q += string_format(
			"UPDATE stats SET gold = %d, hunters = %d, str = %d, intel = %d, dex = %d, hp = %d, max_hp = %d, mana = %d, max_mana = %d, groupid = %d, lvl = %d, exp = %d WHERE name = \"%s\"; ",
			it->second->gold,
			it->second->hunters,
			it->second->str,
			it->second->intel,
			it->second->dex,
			it->second->hp,
			it->second->max_hp,
			it->second->mana,
			it->second->max_mana,
			it->second->groupid,
			it->second->lvl,
			it->second->exp,
			it->second->name);
	}
	int rc = sqlite3_exec(db, q.c_str(), NULL, 0, NULL);
	if (rc != SQLITE_OK)
		printf("backup failed\n");
	else
		printf("sql backed up\n");
	return (1);
}

int	Server::sendItemList(Player *p, std::map<int, Item *>list)
{
	t_packet	header;

	memcpy(header.id, "SERVER\0", 7);
	memcpy(header.command, "ILIST_HEAD\0", 11);
	memcpy(header.data[0], std::to_string(list.size()).c_str(), std::to_string(list.size()).size());
	write(p->fd, &header, sizeof(t_packet));
	for (std::map<int, Item *>::iterator it = list.begin(); it != list.end(); ++it)
	{
		t_packet	pa;
		memcpy(pa.id, "SERVER\0", 7);
		memcpy(pa.command, "ITEM\0", 5);
		memcpy(pa.data[0], std::to_string(it->second->instance_id).c_str(), std::to_string(it->second->instance_id).size());
		memcpy(pa.data[1], std::to_string(it->second->base_id).c_str(), std::to_string(it->second->base_id).size());
		memcpy(pa.data[2], std::to_string(it->second->rarity).c_str(), std::to_string(it->second->rarity).size());
		memcpy(pa.data[3], std::to_string(it->second->enchants[0]).c_str(), std::to_string(it->second->enchants[0]).size());
		memcpy(pa.data[4], std::to_string(it->second->enchants[1]).c_str(), std::to_string(it->second->enchants[1]).size());
		memcpy(pa.data[5], std::to_string(it->second->enchants[2]).c_str(), std::to_string(it->second->enchants[2]).size());
		memcpy(pa.data[6], std::to_string(it->second->enchants[3]).c_str(), std::to_string(it->second->enchants[3]).size());
		memcpy(pa.data[7], std::to_string(it->second->enchants[4]).c_str(), std::to_string(it->second->enchants[4]).size());
		memcpy(pa.data[8], std::to_string(it->second->scale[0]).c_str(), std::to_string(it->second->scale[0]).size());
		memcpy(pa.data[9], std::to_string(it->second->scale[1]).c_str(), std::to_string(it->second->scale[1]).size());
		memcpy(pa.data[10], std::to_string(it->second->scale[2]).c_str(), std::to_string(it->second->scale[2]).size());
		memcpy(pa.data[11], std::to_string(it->second->scale[3]).c_str(), std::to_string(it->second->scale[3]).size());
		memcpy(pa.data[12], std::to_string(it->second->scale[4]).c_str(), std::to_string(it->second->scale[4]).size());
		bzero(pa.data[13], 16);
		write(p->fd, &pa, sizeof(t_packet));
	}
	return (1);
}

int	Server::awardKill(Player *p)
{
	printf("%s gets %d exp\n", p->name, (p->lvl * 100) / 4);
	int e = ((p->lvl * 100) / 4) * p->mon.count;
	int g = (((rand() % (p->lvl + 5)) + 1) * 100) * p->mon.count;
	p->exp += e;
	p->gold += g;
	notify(p, string_format("You've killed some monsters, gaining %d gold and %d experience.", g, e));
	if (p->exp >= (p->lvl * 1000))
	{
		p->lvl++;
		p->max_hp += 20;
		p->max_mana += 20;
		p->hp = p->max_hp;
		p->mana = p->max_mana;
		p->str += 2;
		p->dex += 1;
		p->intel += 1;
		p->exp -= (p->lvl - 1) * 1000;
		notify(p, string_format("You've reached level %d!\n", p->lvl));
	}
	return (1);
}

int	Server::removePlayer(Player *p)
{
	printf("%s dc\n", p->name);
	FD_CLR(p->fd, &active_fd_set);
	close(p->fd);
	p->fd = -1;
	return (1);
}

static int	playerLoad(void *d, int argc, char **argv, char **colName)
{
	if (!argc || !colName)
		return (0);
	std::map<std::string, Player *> *ret = (std::map<std::string, Player *>*)d;
	Player *pl = new Player();
	memcpy(pl->name, argv[0], 16);
	printf("[%s]\n", pl->name);
	pl->name[strlen(argv[0])] = 0;
	pl->gold = std::atoi(argv[1]);
	pl->hunters = std::atoi(argv[2]);
	pl->str = std::atoi(argv[3]);
	pl->intel = std::atoi(argv[4]);
	pl->dex = std::atoi(argv[5]);
	pl->hp = std::atoi(argv[6]);
	pl->max_hp = std::atoi(argv[7]);
	pl->mana = std::atoi(argv[8]);
	pl->max_mana = std::atoi(argv[9]);
	pl->groupid = std::atoi(argv[10]);
	pl->lvl = std::atoi(argv[11]);
	pl->exp = std::atoi(argv[12]);
	pl->fd = -1;
	ret->insert(std::pair<std::string, Player *>(std::string(argv[0]), pl));
	printf("[%s]\n", argv[1]);
	return (0);
}

static int	verify_callback(void *d, int argc, char **argv, char **colNames)
{
	int	*r = (int*)d;
	if (argc)
		*r = 1;
	else if (!argc || !argv || !colNames)
		*r = -1;
	return (1);
}

int	Server::loadPlayers()
{
	std::string q = ("SELECT * from stats;");
	int ret = sqlite3_exec(db, q.c_str(), playerLoad, (void*)&players, NULL);
	if (ret != SQLITE_OK)
		printf("player load failed %d\n", ret);
	return (1);
}

static int	baseLoad(void *d, int argc, char **argv, char **colname)
{
	if (!argc || !colname)
		return (0);
	ItemBase	*new_item = new ItemBase(argv);
	std::map<int, ItemBase *> *list = (std::map<int, ItemBase *>*)d;
	list->insert(std::pair<int, ItemBase *>(new_item->id, new_item));
	return (0);
}

int	Server::loadBases()
{
	std::string q = ("SELECT * from item_base;");
	int ret = sqlite3_exec(db, q.c_str(), baseLoad, (void*)&item_bases, NULL);
	if (ret != SQLITE_OK)
		printf("base load failed %d\n", ret);
	return (1);
}

static int	auraLoad(void *d, int argc, char **argv, char **colname)
{
	if (!argc || !colname)
		return (0);
	Aura	*a = new Aura(argv);
	std::map<int, Aura *> *list = (std::map<int, Aura *>*)d;
	list->insert(std::pair<int, Aura *>(a->id, a));
	return (0);
}

int	Server::loadAuras()
{
	std::string	q = ("SELECT * from auras;");
	int ret = sqlite3_exec(db, q.c_str(), auraLoad, (void*)&auras, NULL);
	if (ret != SQLITE_OK)
		printf("aura load failed %d\n", ret);
	return (1);
}

int	Server::newPlayer(t_packet *pack, int nfd)
{
	Player	*pl = new Player();
	std::string	q = string_format("INSERT INTO users (name, pass) VALUES (\"%s\", \"%s\"); INSERT INTO stats (name, gold, hunters, str, intel, dex, hp, max_hp, mana, max_mana, groupid, lvl, exp) VALUES (\"%s\", 100, 1, 10, 10, 10, 100, 100, 100, 100, 0, 1, 0);", pack->id, pack->data[0], pack->id);

	int rc = sqlite3_exec(db, q.c_str(), NULL, 0, NULL);
	if (rc != SQLITE_OK)
		printf("player creation failed\n");
	memcpy(pl->name, pack->id, 16);
	memcpy(pl->pass, pack->data[0], 16);
	pl->fd = nfd;
	pl->gold = 100;
	pl->hunters = 1;
	pl->str = 10;
	pl->intel = 10;
	pl->dex = 10;
	pl->hp = 100;
	pl->max_hp = 100;
	pl->mana = 100;
	pl->max_mana = 100;
	pl->groupid = 0;
	pl->lvl = 1;
	pl->exp = 0;
	players.insert(std::pair<std::string, Player *>(std::string(pl->name), pl));
	return (1);
}

int	Server::sendStatus(Player *p)
{
	t_packet	pack;
	std::string	g = std::to_string(p->gold);
	std::string h = std::to_string(p->hunters);
	std::string	_str = std::to_string(p->str);
	std::string _intel = std::to_string(p->intel);
	std::string _dex = std::to_string(p->dex);
	std::string _hp = std::to_string(p->hp);
	std::string _max_hp = std::to_string(p->max_hp);
	std::string _mana = std::to_string(p->mana);
	std::string _max_mana = std::to_string(p->max_mana);
	std::string _groupid = std::to_string(p->groupid);
	std::string _lvl = std::to_string(p->lvl);
	std::string _exp = std::to_string(p->exp);

	memcpy(pack.id, "SERVER", 7);
	memcpy(pack.command, "STATUS", 7);
	memcpy(pack.data[0], g.c_str(), strlen(g.c_str()) + 1);
	memcpy(pack.data[1], h.c_str(), strlen(h.c_str()) + 1);
	memcpy(pack.data[2], _str.c_str(), _str.size() + 1);
	memcpy(pack.data[3], _intel.c_str(), _intel.size() + 1);
	memcpy(pack.data[4], _dex.c_str(), _dex.size() + 1);
	memcpy(pack.data[5], _hp.c_str(), _hp.size() + 1);
	memcpy(pack.data[6], _max_hp.c_str(), _max_hp.size() + 1);
	memcpy(pack.data[7], _mana.c_str(), _mana.size() + 1);
	memcpy(pack.data[8], _max_mana.c_str(), _max_mana.size() + 1);
	memcpy(pack.data[9], _groupid.c_str(), _groupid.size() + 1);
	memcpy(pack.data[10], _lvl.c_str(), _lvl.size() + 1);
	memcpy(pack.data[11], _exp.c_str(), _exp.size() + 1);
	if (write(p->fd, &pack, sizeof(t_packet)) <= 0)
		printf("error writing to fd: %d\n", p->fd);
	return (write(p->fd, &pack, sizeof(t_packet)));
}

int	Server::sendChat(t_packet *pack)
{
	for (std::map<std::string, Player *>::iterator it = players.begin(); it != players.end(); ++it)
		write(it->second->fd, pack, sizeof(t_packet));
	return (1);
}

int	Server::loginRequest(t_packet *pack)
{
	int	ret = 0;
	std::string	q = string_format("SELECT * from users where name = \"%s\" and pass = %s;", pack->id, pack->data[0]);
	printf("CMP %s %s\n", pack->id, pack->data[0]);
	sqlite3_exec(db, q.c_str(), verify_callback, (void*)&ret, NULL);
	return (ret);
}

int	Server::processPacket(t_packet *pack, int nfd)
{
	std::string	plr(pack->id);
	std::string	cmd(pack->command);
	Player		*p = players.find(plr)->second;

	if (cmd.compare("BUY_HUNTER") == 0)
	{
		int	amt = atoi(pack->data[0]);
		if (p->gold >= (100 * amt))
		{
			p->gold -= (100 * amt);
			p->hunters += amt;
		}
		sendStatus(p);
		return (1);
	}
	else if (cmd.compare("CHAT") == 0)
	{
		sendChat(pack);
		return (1);
	}
	else if (cmd.compare("REQ_LOGIN") == 0)
	{
		if (loginRequest(pack) == 1)
		{
			p->fd = nfd;
			sendStatus(p);
			return (1);
		}
		else
		{
			removePlayer(p);
			return (-1);
		}
	}
	else
		printf("unhandled command: %s\n", cmd.c_str());
	return (1);
}

int	Server::playerExists(t_packet *pack)
{
	std::string	str(pack->id);

	std::cout << str << std::endl;
	if (players.find(str) != players.end())
	{
		printf("player %s exists\n", pack->id);
		return (1);
	}
	else
		printf("player %s does not exist, create\n", pack->id);
	return (0);
}

Server::~Server()
{
	sqlite3_close(db);
	std::cout << "Dead.\n";
}
