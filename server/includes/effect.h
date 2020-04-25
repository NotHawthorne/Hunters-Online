#ifndef EFFECT_H
# define EFFECT_H

class Player;
class Monster;
class Item;
# include "player.h"

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
	HEALTH = 13,
	CLEAVE = 14,
	BLEED = 15,
	ARMOR_BUFF = 16
};

static char	*EffectStrings[17] = {
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
	"health",
	"cleave",
	"bleed",
	"armor"
};

class	Aura {
public:
	int		id;
	int		enchant;
	int		val;
	int		proc_rate;
	int		tier;

	Aura(char **argv);
	int		process(Player *p, Item *i, std::map<int, ItemBase*> *bases,
						t_combat_frame *cb_frame, int scale);
	int		proc(Player *p, Monster *m, int scale);
	int		apply(Player *p, int scale);
	int		remove(Player *p, int scale);
};

#endif
