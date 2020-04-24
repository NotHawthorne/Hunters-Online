#ifndef ITEM_H
# define ITEM_H

# include <string>
# include <stdlib.h>
# include <string.h>
# include "packet.h"

enum	Item_Types
{
	JUNK = 0,
	ARMOR = 1,
	WEAPON = 2,
	JEWELLERY = 3
};

static char	*Item_Type_String[4] = {
	"Junk",
	"Armor",
	"Weapon",
	"Jewellery"
};

enum	Item_Armor_Classes
{
	LIGHT,
	MEDIUM,
	HEAVY
};

static char	*Item_Armor_Class_String[3] = {
	"Light",
	"Medium",
	"Heavy",
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

static char	*Item_Weapon_Class_String[13] = {
	"Sword",
	"Shield",
	"Mace",
	"Axe",
	"Dagger",
	"Glaive",
	"Knuckles",
	"Sceptre",
	"Bow",
	"Crossbow",
	"Pistol",
	"Rifle",
	"Staff"
};

enum	Item_Jewellery_Classes
{
	RING,
	NECKLACE
};

static char	*Item_Jewellery_Class_String[2] = {
	"Ring",
	"Necklace"
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

static char	*Item_Slot_String[13] = {
	"Head",
	"Shoulders",
	"Chest",
	"Legs",
	"Feet",
	"Hands",
	"Wrists",
	"Waist",
	"Neck",
	"Finger1",
	"Finger2",
	"Main Hand",
	"Off-Hand"
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
