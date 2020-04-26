#ifndef ITEM_H
# define ITEM_H

# include <string>
# include <stdlib.h>
# include <string.h>
# include "packet.h"

enum	Item_Rarity_Colors
{
	COMMON = 4,
	UNCOMMON = 5,
	RARE = 6,
	EPIC = 7,
	LEGENDARY = 8,
	MYTHIC = 9,
	SPECIAL = 10
};

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

/*						2/5 for uncommon, 3/5 for rare, 4/5 for epic			
alan's ideas:					v
item rarity could gate the amount of auras an item gets (looks like this already hapens, makes a lot of sense)
auras could have rarity		 <- requires instanciation of auras
	like only chain lightning gets applied to rarity 4-5 items
	strength/damage are more common and can get applied to rarity 1
	would make less common items do more better shit
		a rare low-level sword could have tier 1 chain lightning
		would be fuckin rad on an early weapon
			^
			specific defined abilites would be neat, a la Path of Exile Uniques / D3 Legendaries [[[AURA TIERS MAKE THIS POSSIBLE]]]

		and if you gate the cool auras on item rarity then it makes cool effects (that do more) harder to get and more desirable
past alan: you shouldn't be able to move auras. this is why (watch as past alan slowly changes his mind)
	their data should be generated per item, based on rules in the aura and the item's base level ONLY
	the aura loses meaning while not attached to the item it was generated for
		this changes if you have "aura of lifesteal", or "tier 4 aura of lifesteal"
		then a aura type could get re-applied to a new item
	i like the idea of "aura rarity", somewhat gated by item rarity for generated auras
	this means that: tier 4 chain lightning auras are hella rare, because they make any item beaucoup good
	which makes sense, because it can only get generated initially on a high level (level 70-90) item
	if aura tier is based on item level, then higher tier auras when removed could still get applied to anythning
	would be neat if that was an economy driver, would definitely give a reason to sell items
	if you could "repurpose" items and shuck their auras for the market or use them after buying a item with an aura you want
	i still don't know if i like an aura market
	but it would definitely make sense
if auras can't be moved:
	items are the only thing that matter
	it doesn't matter what auras do as much as they scale with your player level
	here's what I don't want to see with aura scaling:
		[x] items at certain levels are "sweet spots" for auras
		[o] one single aura doubling the damage output of an item
			because then you get carried a level or two without needing to equip
			and if you're supposed to have a full set of gear, then things get silly
			well, if you think about the loadout I had, it kinda makes sense a little for level 30
			I just got there too fast
			I didn't have a full loadout of gear but the gear that I had was p good
		i need to slow down the internal head scale for level up speed i think
		your first full set of gear should maybe have 2-3 auras equipped total
		these should be pretty necessary to get you to the next stage of gear
		if the item base damage is all the same, then a lot of loadouts with no auras are pretty similar
		this is nice because it means you're gated entirely on player level/monster level/item level
		you simply have to fight better monsters to get higher level items
		but then once you hit level 5 or 6, and you get your first piece of aura gear,
			maybe the low rarity auras are base stat buffs <- ties into enchant masks
			so you find a ring that makes you feel quicker (dex boost)
			you can now get critical strikes more often!
			maybe you find a shoulder pad that not only has base defense, but increases your actual player defense
																											|
																											 ->working on this
*/

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
