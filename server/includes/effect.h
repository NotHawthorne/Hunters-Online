#ifndef EFFECT_H
# define EFFECT_H

class Player;
class Monster;
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

static char	*EffectStrings[14] = {
	"none",
	"phys damage",
	"atk spd",
	"crit chance",
	"crit mult",
	"int",
	"str",
	"dex",
	"lifesteal",
	"stun",
	"chain lightning",
	"poison",
	"heal",
	"health" 
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
