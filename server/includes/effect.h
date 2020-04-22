#ifndef EFFECT_H
# define EFFECT_H

# include "player.h"

enum	Effects
{
	PHYS_DMG,
	ATK_SPD,
	CRIT_CHANCE,
	CRIT_MULT,
	INT,
	STR,
	DEX,
	LIFESTEAL,
	STUN,
	CHAIN_LIGHTNING,
	POISON,
	HEAL,
	HEALTH
};

class	Aura {
public:
	int		id;
	int		enchant;
	int		val;
	int		proc_rate;
	int		tier;

	Aura(char **argv);
	int		proc(Player *p, Monster *m, int scale);
	int		apply(Player *p, int scale);
	int		remove(Player *p, int scale);
};

#endif
