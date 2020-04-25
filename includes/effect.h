#ifndef EFFECT_H
# define EFFECT_H

# include <stdlib.h>
# include <cstring>

enum	Effects
{
	PHYS_DMG = 1,
	ATK_SPD = 2,
	CRIT_CHANCE = 3,
	CRIT_MULT = 4,
	INT = 5,
	STR = 6,
	DEX = 7,
	LIFESTEAL = 8,
	STUN = 9,
	CHAIN_LIGHTNING = 10,
	POISON = 11,
	HEAL = 12,
	HEALTH = 13
};

static char	EffectStrings[][32] = {
	"none",
	"physical damage",
	"attack speed",
	"critical strike chance",
	"critical strike multiplier",
	"intellect",
	"strength",
	"dexterity",
	"lifestealing",
	"stun",
	"chain lightning",
	"poison",	//strength and decay
	"heal",
	"health",
	"cleave",	//TODO
	"bleed"		//TODO
};

class	Aura {
public:
	int		id;
	int		enchant;
	int		val;
	int		proc_rate;
	int		tier;
	char	title[16];
	int		pre;

	Aura(char **argv);
};

#endif
