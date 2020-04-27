#ifndef PLAYER_H
# define PLAYER_H

class Server;
# include <map>
# include <string>
# include "item.h"

typedef struct	s_combat_frame
{
	int		dmg;
	int		strbuff;
	int		dexbuff;
	int		intbuff;
	int		lifesteal_amt;
	int		heal_amt;
	int 	armor_mit;
	int 	max_hp_mod;
	bool	crit;
	int		dot[5];
	int		dec[5];
	int		next_tick;
}				t_combat_frame;

class	Monster {
public:
	char	name[16];
	int		id;
	int		level;
	int		hp;
	int		dmg;
	int		armor;
	int		count;
	Monster();
};

class	Area {
	char	name[32];
	int		level_min;
	int		level_max;
	int		monster_ids[5];
};

class	Player {
public:
	char	name[32];
	char	pass[16];
	int		fd;
	std::map<int, Item *>	inventory;
	std::map<int, Item *>	equip;
	PacketQueue	*packet_queue;
	Monster	mon;
	int		gold;
	int		hunters;

	int		str;
	int		intel;
	int		dex;
	int		hp;
	int		max_hp;
	int		mana;
	int		max_mana;
	int		groupid;
	int		lvl;
	int		exp;
	int		gold_exponent;

	int		area;

	int		tick(Server *s);

	int		access;

	t_combat_frame	*fr;
	Player();
	~Player();
};

#endif
