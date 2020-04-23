#ifndef PLAYER_H
# define PLAYER_H

# include <map>
# include <string>
# include "item.h"

class	Monster {
public:
	int		level;
	int		hp;
	int		dmg;
	int		count;
};

class	Player {
public:
	char	name[32];
	char	pass[16];
	int		fd;
	std::map<int, Item *>	inventory;
	Item	*equip[13];
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

	int		tick();
};

#endif
