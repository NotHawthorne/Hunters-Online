#include "../../includes/client.h"

int	Hunters_Online::Client::sendPacket(char *id, char *command,
									char **data)
{
	t_packet	p;

	bzero(&p.id, 16);
	bzero(&p.command, 16);
	strncpy(p.id, id, strlen(id));
	strncpy(p.command, command, strlen(command));
	for (int i = 0; data && data[i]; i++)
		strncpy(p.data[i], data[i], strlen(data[i]));
	write(conn_fd, &p, sizeof(t_packet));
	fflush(0);
	return (1);
}

std::string	Hunters_Online::Client::constructItemNameStr(Item *i)
{
	std::string	item_name(item_base[i->base_id]->name);
	int	pre = 0;
	int	post = 0;
	for (int x = 0; x != 5; x++)
	{
		if (i->enchants[x])
		{
			if (auras[i->enchants[x]]->pre)
				pre = i->enchants[x];
			else
				post = i->enchants[x];
		}
	}
	if (!pre && !post)
		return (item_name);
	std::string	ret("");
	if (pre)
		ret += auras[pre]->title;
	ret += item_name;
	if (post)
		ret += auras[post]->title;
	return (ret);
}

int	Hunters_Online::Client::updateDisplay(WINDOW *win, int new_state)
{
	if (state == last_state)
		return (0);
	last_state = state;
	state = new_state;
	wclear(win);
	wrefresh(win);
	auto ite = inventory.begin();
	auto pit = plist.begin();
	std::map<int, Item *>::iterator it_eq = equipment.begin();
	int x = 0;
	int n = ((LINES * 0.75) - 3) * inven_page;
	Item **ia = new Item*[13];
	switch (state)
	{
		case WELCOME:
			wprintw(win, WELCOME_MSG);
			break ;
		case EQUIPMENT:
			wprintw(win, "equipment (%d/13):\n", equipment.size());
			for (int y = 0; y != 13; y++)
				ia[y] = NULL;
			for (int y = 0; y != 13; y++)
				if (equipment.find(y) != equipment.end())
					ia[item_base[equipment[y]->base_id]->slot] = equipment[y];
			while (x < 13)
			{
				if (ia[x])
				{
					wattron(win, COLOR_PAIR((ia[x]->rarity + 3) > SPECIAL ? SPECIAL : (ia[x]->rarity + 3)));
					wprintw(win, "%-16s -- %s\n", Item_Slot_String[x], constructItemNameStr(ia[x]).c_str());
					wattron(win, COLOR_PAIR(COMMON));
				}
				else
					wprintw(win, "%-16s -- empty\n", Item_Slot_String[x]);
				x++;
			}
			break ;
		case INVENTORY:
			if (((LINES * 0.75) - 3) * inven_page > inventory.size())
				break ;
			std::advance(ite, ((LINES * 0.75) - 3) * inven_page);
			while (x < (LINES * 0.75) - 4 && ite != inventory.end())
			{
				wattron(win, COLOR_PAIR((ite->second->rarity + 3) > SPECIAL ? SPECIAL : (ite->second->rarity + 3)));
				wprintw(win, "%-8d -- %s\n", x + n, constructItemNameStr(ite->second).c_str()); 
				wattron(win, COLOR_PAIR(COMMON));
				ite++;
				x++;
			}
			wprintw(win, "page: %d", inven_page + 1);
			//for (int i = 1 + (((LINES / 0.75) - 3) * inven_page); i < 1 + ((((LINES / 0.75) - 3) * (inven_page + 1))) && i < inventory.size(); i++)
				//wprintw(win, "%s\n", item_base[inventory[i]->base_id]->name);
			break ;
		case HOME:
			wprintw(win, "empty");
			break ;
		case EINSPECT:
			if (inspect_slot >= 13 || (it_eq = equipment.find(inspect_slot)) == equipment.end())
				break ;
			it_eq = equipment.find(inspect_slot);
			//std::advance(it_eq, inspect_slot);
			wattron(win, COLOR_PAIR((it_eq->second->rarity + 3) > SPECIAL ? SPECIAL : (it_eq->second->rarity + 3)));
			wprintw(win, "[%s] (Equipped)\n", constructItemNameStr(it_eq->second).c_str());
			wattron(win, COLOR_PAIR(COMMON));
			wprintw(win, "%s | %s | req: %d\n",
				Item_Type_String[item_base[it_eq->second->base_id]->item_type],
				Item_Slot_String[item_base[it_eq->second->base_id]->slot],
				item_base[it_eq->second->base_id]->item_levreq);
			if (item_base[it_eq->second->base_id]->item_type == ARMOR)
				wprintw(win, "%s\n", Item_Armor_Class_String[item_base[it_eq->second->base_id]->item_class]);
			else if (item_base[it_eq->second->base_id]->item_type == WEAPON)
				wprintw(win, "%s\n", Item_Weapon_Class_String[item_base[it_eq->second->base_id]->item_class]);
			else if (item_base[it_eq->second->base_id]->item_type == JEWELLERY)
				wprintw(win, "%s\n", Item_Jewellery_Class_String[item_base[it_eq->second->base_id]->item_class]);
			else
				break ;
			if (item_base[it_eq->second->base_id]->damage_min > 0)
				wprintw(win, "%d - %d dmg\n", item_base[it_eq->second->base_id]->damage_min, item_base[it_eq->second->base_id]->damage_max);
			if (item_base[it_eq->second->base_id]->armor > 0)
				wprintw(win, "%d armor\n", item_base[it_eq->second->base_id]->armor);
			wprintw(win, "ilvl: %d\n", item_base[it_eq->second->base_id]->level);
			for (int i = 0; i < 5 && it_eq->second->enchants[i]; i++)
				wprintw(win, finalAuraInfoString(auras[it_eq->second->enchants[i]], it_eq->second, i).c_str());
			//wprintw(win, "%s (%d)\n", EffectStrings[auras[it_eq->second->enchants[i]]->enchant], it_eq->second->scale[i]);
			break ;
		case INSPECT:
			if (inspect_slot >= inventory.size())
				break ;
			std::advance(ite, inspect_slot);
			wattron(win, COLOR_PAIR((ite->second->rarity + 3) > SPECIAL ? SPECIAL : (ite->second->rarity + 3)));
			wprintw(win, "[%s]\n", constructItemNameStr(ite->second).c_str());
			wattron(win, COLOR_PAIR(COMMON));
			wprintw(win, "%s | %s | req: %d\n",
				Item_Type_String[item_base[ite->second->base_id]->item_type],
				Item_Slot_String[item_base[ite->second->base_id]->slot],
				item_base[ite->second->base_id]->item_levreq);
			if (item_base[ite->second->base_id]->item_type == ARMOR)
				wprintw(win, "%s\n", Item_Armor_Class_String[item_base[ite->second->base_id]->item_class]);
			else if (item_base[ite->second->base_id]->item_type == WEAPON)
				wprintw(win, "%s\n", Item_Weapon_Class_String[item_base[ite->second->base_id]->item_class]);
			else if (item_base[ite->second->base_id]->item_type == JEWELLERY)
				wprintw(win, "%s\n", Item_Jewellery_Class_String[item_base[ite->second->base_id]->item_class]);
			else
				break ;
			if (item_base[ite->second->base_id]->damage_min > 0)
				wprintw(win, "%d - %d dmg\n", item_base[ite->second->base_id]->damage_min, item_base[ite->second->base_id]->damage_max);
			if (item_base[ite->second->base_id]->armor > 0)
				wprintw(win, "%d armor\n", item_base[ite->second->base_id]->armor);
			wprintw(win, "ilvl: %d (%d)\n", item_base[ite->second->base_id]->level, ite->second->enchants[1]);
			for (int i = 0; i < 5 && ite->second->enchants[i]; i++)
				wprintw(win, finalAuraInfoString(auras[ite->second->enchants[i]], ite->second, i).c_str());
			//wprintw(win, "%s (%d)\n", EffectStrings[auras[ite->second->enchants[i]]->enchant], ite->second->scale[i]);
			break ;
		case PLAYERS:
			for (int i = 0; i != (LINES * 0.75) - 3 && i < plist.size(); i++)
			{
				wprintw(win, "%s, level %d\n", pit->second->name, pit->second->level);
				pit++;
			}
			break ;
		default:
			break ;
	}
	delete[] ia;
	wrefresh(win);
	return (1);
}

int	Hunters_Online::Client::sendChat(char *data, size_t len, bool whisper, char *dst)
{
	t_packet	p;
	int			x = 0;
	int			y = 0;
	std::string	l;

	bzero(&p.id, 16);
	bzero(&p.command, 16);
	strncpy(p.id, name, strlen(name));
	strncpy(p.command, whisper == true ? "WHIS\0" : "CHAT\0", 5);
	if (whisper == true)
	{
		bzero(p.data[x], 16);
		memcpy(p.data[x++], dst, strlen(dst));
	}
	l = std::to_string((int)len);
	strncpy(p.data[x++], l.c_str(), l.size() + 1);
	for (int i = 0; i < (int)len && data[i] && x < 30; i += 15)
	{
		bzero(p.data[x], 16);
		memcpy(p.data[x++], data + i, len - i > 16 ? 15 : len - i);
	}
	bzero(p.data[x], 16);
	write(conn_fd, &p, sizeof(t_packet));
	fflush(0);
	return (1);
}

t_packet	*Hunters_Online::Client::recvItemList(std::map<int, Item *> *l, t_packet *h, int type)
{
	int	amt = std::atoi(h->data[0]);
	int i = 0;

	while (i < amt)
	{
		char		data[sizeof(t_packet)];
		t_packet	*p;
		int			tmp;
		int			rbytes;

		rbytes = read(conn_fd, data, sizeof(t_packet));
		if (rbytes < 0)
			continue ;
		while (rbytes > 0 && rbytes < sizeof(t_packet))
		{
			tmp = read(conn_fd, data + rbytes, sizeof(t_packet) - rbytes);
			if (tmp > 0)
				rbytes += tmp;
		}
		p = (t_packet *)&data;
		if (rbytes == sizeof(t_packet) && strcmp(p->command, "ITEM") != 0)
		{
			return (NULL); // fuck memory allocation i guess it just wont fucking work as a
							// return value that i can free later
		}

		Item	*ite = new Item(p);
		l->insert(std::pair<int, Item *>(type == 1 ? item_base[ite->base_id]->slot : l->size(), ite));
		i++;
		usleep(5);
	}
	return (NULL);
}

t_packet	*Hunters_Online::Client::recvUserList(std::map<int, Player *> *l, t_packet *h)
{
	int	amt = std::atoi(h->data[0]);
	int i = 0;

	while (i < amt)
	{
		char		data[sizeof(t_packet)];
		t_packet	*p;
		int			tmp;
		int			rbytes;

		rbytes = read(conn_fd, data, sizeof(t_packet));
		if (rbytes < 0)
			continue ;
		while (rbytes > 0 && rbytes < sizeof(t_packet))
		{
			tmp = read(conn_fd, data + rbytes, sizeof(t_packet) - rbytes);
			if (tmp > 0)
				rbytes += tmp;
		}
		p = (t_packet *)&data;
		if (rbytes == sizeof(t_packet) && strcmp(p->command, "PLAYER") != 0)
		{
			printf("%s\n", p->command);
			//t_packet	*ret = (t_packet*)malloc(sizeof(t_packet));
			//memcpy(&ret, data, sizeof(t_packet)); SEE ABOVE
			return (NULL);
		}
		printf("HI I GUESS\n");
		Player	*np = new Player(p);
		l->insert(std::pair<int, Player *>(l->size(), np));
		i++;
		usleep(5);
	}
	return (NULL);
}

Hunters_Online::Client::Client()
{
	int		ret;
	std::string	pass_hash;
	std::hash<std::string>	hasher;

	state = WELCOME;
	last_state = -1;
	inven_page = 0;
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	ret = inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr);
	conn_fd = -1;
	if (!ret)
		return ;
	conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (conn_fd <= 0)
		return ;
	ret = connect(conn_fd, (struct sockaddr*)&server_addr,
					sizeof(server_addr));
	if (ret < 0)
		return ;
	int flags = fcntl(conn_fd, F_GETFL);
	fcntl(conn_fd, F_SETFL, flags | O_NONBLOCK);
	initDB();
}

static int	item_base_load_callback(void *d, int argc, char **argv, char **colname)
{
	if (!argc || !colname)
		return (1);
	ItemBase	*b = new ItemBase(argv);
	std::map<int, ItemBase *> *list = (std::map<int, ItemBase *>*)d;
	list->insert(std::pair<int, ItemBase *>(b->id, b));
	return (0);
}

static int	auras_load_callback(void *d, int argc, char **argv, char **colname)
{
	if (!argc || !colname)
		return (1);
	Aura	*a = new Aura(argv);
	std::map<int, Aura *> *list = (std::map<int, Aura *>*)d;
	list->insert(std::pair<int, Aura *>(a->id, a));
	return (0);
}

int	Hunters_Online::Client::initDB()
{
	std::string iq = "SELECT * FROM item_base;";
	std::string	aq = "SELECT * FROM auras;";

	int	rc = sqlite3_open("./info.db", &db);
	int	ret = 0;
	if (rc)
		printf("db init failed\n");
	ret = sqlite3_exec(db, iq.c_str(), item_base_load_callback, (void*)&item_base, NULL);
	if (ret != SQLITE_OK)
		printf("item load failed\n");
	ret = sqlite3_exec(db, aq.c_str(), auras_load_callback, (void*)&auras, NULL);
	if (ret != SQLITE_OK)
		printf("aura load failed\n");
	return (1);
}

Hunters_Online::Client::~Client()
{
	inventory.clear();
	equipment.clear();
	auras.clear();
	item_base.clear();
	plist.clear();
	close(conn_fd);
}

std::string	Hunters_Online::Client::finalAuraInfoString(Aura *a, Item *i, int idx)
{
	std::string	info("");
	if (a->proc_rate)
		info += string_format("%d chance for ", a->proc_rate);
	switch (a->enchant)
	{
		case PHYS_DMG:
			info += string_format("+%d physical damage", (int)(a->val * (i->scale[idx] / 100.0)) + 1);
			break ;
		case CRIT_CHANCE:
			info += string_format("+%d chance to crit", int(a->val * (i->scale[idx] / 100.0)) + 1);
			break ;
		case STR:
			info += string_format("+%d strength", (int)(a->val * (i->scale[idx] / 100.0)) + 1);
			break ;
		case INT:
			info += string_format("+%d intellect", (int)(a->val * (i->scale[idx] / 100.0)) + 1);
			break ;
		case STUN:
			info += string_format("+%d tick stun", a->val);
			break ;
		case HEALTH:
			info += string_format("+%d health", (int)(a->val * (i->scale[idx] / 100.0)) + 1);
			break ;
		case HEAL:
			info += string_format("+%d healing", (int)(a->val * (i->scale[idx] / 100.0)) + 1);
			break ;
		case CHAIN_LIGHTNING:
			info += string_format("chain lightning that deals %d damage and bounces three times", ((int)(a->val * (i->scale[idx] / 100.0)) + 1));
			break ;
		case LIFESTEAL:
			info += string_format("stealing %d health", (int)(a->val * (i->scale[idx] / 100.0)) + 1);
			break ;
	}
	info += "\n";
	return (info);
}
