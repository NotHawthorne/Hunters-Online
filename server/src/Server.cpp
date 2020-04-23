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
	std::cout << "Loading item instances...\n";
	loadInstances();
	std::cout << "Loaded " << items.size() << " item instances!\n";
	std::cout << "Loading inventories...\n";
	loadInventories();
	std::cout << "done!\n";
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
			"UPDATE stats SET gold = %d, hunters = %d, str = %d, intel = %d, dex = %d, hp = %d, max_hp = %d, mana = %d, max_mana = %d, groupid = %d, lvl = %d, exp = %d, gold_exponent = %d WHERE name = \"%s\"; ",
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
			it->second->gold_exponent,
			it->second->name);
	}
	int rc = sqlite3_exec(db, q.c_str(), NULL, 0, NULL);
	if (rc != SQLITE_OK)
		printf("backup failed\n");
	else
		printf("sql backed up\n");
	return (1);
}

int	Server::sendItemList(Player *p, std::map<int, Item *> *list, int type)
{
	t_packet	header;

	memcpy(header.id, "SERVER\0", 7);
	memcpy(header.command, "ILIST_HEAD\0", 11);
	bzero(header.data[0], 16);
	bzero(header.data[1], 16);
	memcpy(header.data[0], std::to_string(list->size()).c_str(), std::to_string(list->size()).size());
	memcpy(header.data[1], std::to_string(type).c_str(), std::to_string(type).size());
	write(p->fd, &header, sizeof(t_packet));
	for (std::map<int, Item *>::iterator it = list->begin(); it != list->end(); ++it)
	{
		t_packet	pa;
		memcpy(pa.id, "SERVER\0", 7);
		memcpy(pa.command, "ITEM\0", 5);
		for (int i = 0; i != 15; i++)
			bzero(pa.data[i], 16);
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

Item	*Server::genItem(int level)
{
	Item	*ni = new Item();

	ItemBase	*ti = item_bases[(rand() % item_bases.size()) + 1];
	Aura	*ta = auras[(rand() % auras.size()) + 1];

	ni->instance_id = items.size();
	printf("instance id: %d\n", ni->instance_id);
	while (ti->level > level)
		ti = item_bases[(rand() % item_bases.size()) + 1];
	ni->base_id = ti->id;
	int		auras_ = (rand() % 5);
	bzero(ni->enchants, sizeof(int) * 5);
	bzero(ni->scale, sizeof(int) * 5);
	ni->rarity = rand() % 100;
	for (int i = 0; i != auras_ && ti->item_type != JUNK; i++)
	{
		while (ta->tier > (level % 10) + 1)
			ta = auras[(rand() % auras.size()) + 1];
		ni->enchants[i] = ta->id;
	}
	for (int i = 0; i != auras_ && ti->item_type != JUNK; i++)
		ni->scale[i] = (rand() % 100);
	items.insert(std::pair<int, Item *>(items.size(), ni));
	std::string	q = string_format("INSERT INTO item_instance(id, base_id, rarity, enc1, enc2, enc3, enc4, enc5, sca1, sca2, sca3, sca4, sca5) VALUES (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d);", ni->instance_id, ni->base_id, ni->rarity, ni->enchants[0], ni->enchants[1], ni->enchants[2], ni->enchants[3], ni->enchants[4], ni->scale[0], ni->scale[1], ni->scale[2], ni->scale[3], ni->scale[4]);
	int ret = sqlite3_exec(db, q.c_str(), NULL, 0, NULL);
	if (ret != SQLITE_OK)
		printf("error saving item\n");
	printf("generated %s!\n", item_bases[ni->base_id]->name);
	return (ni);
}

int		Server::grantItem(Player *p, Item *i)
{
	p->inventory.insert(std::pair<int, Item *>(p->inventory.size(), i));
	std::string q = string_format("INSERT INTO inventory(name, id) VALUES (\"%s\", %d);", p->name, i->instance_id);
	int res = sqlite3_exec(db, q.c_str(), NULL, 0, NULL);
	if (res != SQLITE_OK)
		printf("error granting item\n");
	notify(p, string_format("You've found a %s!", item_bases[i->base_id]->name));
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
	if (rand() % (100 - p->lvl) == 0)
	{
		grantItem(p, genItem(p->lvl));
		sendItemList(p, &p->inventory, 0);
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
	pl->gold_exponent = std::atoi(argv[13]);
	pl->fd = -1;
	ret->insert(std::pair<std::string, Player *>(std::string(argv[0]), pl));
	printf("[%s]\n", argv[1]);
	return (0);
}

static int	verify_callback(void *d, int argc, char **argv, char **colNames)
{
	int	*r = (int*)d;
	printf("actual pass: %s\n", argv[1]);
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

static int	invenLoad(void *d, int argc, char **argv, char **colname)
{
	if (!argc || !colname)
		return (0);
	Server	*s = (Server *)d;
	s->players[std::string(argv[0])]->inventory.insert(std::pair<int, Item *>(std::atoi(argv[1]), s->items[std::atoi(argv[1])]));
	return (0);
}

int	Server::loadInventories()
{
	std::string q = ("SELECT * from inventory;");
	int ret = sqlite3_exec(db, q.c_str(), invenLoad, (void*)this, NULL);
	if (ret != SQLITE_OK)
		printf("inven load failed\n");
	return (1);
}

static int	instanceLoad(void *d, int argc, char **argv, char **colname)
{
	if (!argc || !colname)
		return (0);
	Server *s = (Server *)d;
	Item	*i = new Item(argv);
	s->items.insert(std::pair<int, Item *>(i->instance_id, i));
	return (0);
}

int	Server::loadInstances()
{
	std::string q = ("SELECT * from item_instance;");
	int ret = sqlite3_exec(db, q.c_str(), instanceLoad, (void*)this, NULL);
	if (ret != SQLITE_OK)
		printf("instance load failed\n");
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
	notify(pl, "Successfully registered new acount! Welcome!");
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
	std::string _gold_exponent = std::to_string(p->gold_exponent);

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
	memcpy(pack.data[12], _gold_exponent.c_str(), _gold_exponent.size() + 1);
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

int	Server::respondLogin(int nfd, bool success)
{
	t_packet p;

	printf("responding to login...\n");
	bzero(p.id, 16);
	bzero(p.command, 16);
	for (int i = 0; i != 30; i++)
		bzero(p.data[i], 16);
	memcpy(p.id, "SERVER", 6);
	memcpy(p.command, success ? "AUTH_SUCCESS" : "AUTH_FAIL", success ? 12 : 9);
	printf("%s\n", success ? "succeeded" : "failed");
	write(nfd, &p, sizeof(t_packet));
	return (1);
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
			respondLogin(nfd, true);
			p->fd = nfd;
			sendStatus(p);
			sendItemList(p, &p->inventory, 0);
			notify(p, string_format("[MOTD] %s", MOTD));
			return (1);
		}
		else
		{
			respondLogin(nfd, false);
			removePlayer(p);
			return (-1);
		}
	}
	else if (cmd.compare("WHIS") == 0)
	{
		if (strcmp(pack->data[0], pack->id) == 0)
			notify(p, "You whisper to yourself for a while, hoping nobody notices. What a strange thing to do.");
		else if (players.find(std::string(pack->data[0])) != players.end() && players[std::string(pack->data[0])]->fd > 0)
		{
			write(players[std::string(pack->data[0])]->fd, &(*pack), sizeof(t_packet));
			write(nfd, &(*pack), sizeof(t_packet));
		}
		else
			notify(p, string_format("User %s is offline.", pack->data[0]));
		return (1);
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
