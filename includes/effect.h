#ifndef EFFECT_H
# define EFFECT_H

# include <stdlib.h>
# include <cstring>

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

static char	EffectStrings[][32] = {
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
	char	title[16];
	int		pre;

	Aura(char **argv);
};

#endif
