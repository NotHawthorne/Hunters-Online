#ifndef ITEM_H
# define ITEM_H

# include <string>
# include <stdlib.h>
# include <string.h>
# include "packet.h"

enum	Item_Types
{
	JUNK,
	ARMOR,
	WEAPON,
	JEWELLERY
};

enum	Item_Armor_Classes
{
	LIGHT,
	MEDIUM,
	HEAVY
};

enum	Item_Weapon_Classes
{
	SWORD,
	SHIELD,
	MACE,
	AXE,
	DAGGER,
	GLAIVE,
	KNUCKLES,
	SCEPTRE,
	BOW,
	CROSSBOW,
	PISTOL,
	RIFLE,
	STAFF
};

enum	Item_Jewellery_Classes
{
	RING,
	NECKLACE
};

enum	Item_Slots
{
	HEAD,
	SHOULDERS,
	CHEST,
	LEGS,
	FEET,
	HANDS,
	WRISTS,
	WAIST,
	NECK,
	FINGER1,
	FINGER2,
	MAIN_HAND,
	OFF_HAND
};

class	Item {
public:
	int			instance_id;
	int			base_id;
	int			rarity;
	int			enchants[5];
	int			scale[5];

	Item(t_packet *pack);
};

class	ItemBase {
public:
	int			id;
	char		name[16];
	int			item_type;
	int			item_class;
	int			item_levreq;
	int			damage_min;
	int			damage_max;
	int			speed;
	int			armor;
	int			level;
	int			slot;

	ItemBase(char **argv);
};

#endif
