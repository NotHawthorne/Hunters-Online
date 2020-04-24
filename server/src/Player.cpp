#include "../includes/Server.hpp"

int	Player::tick(Server *s)
{
	unsigned int		gold_gained = 0;
	int					dmg = 0;
	int					strbuff = 0;
	int					dexbuff = 0;
	int					intbuff = 0;
	int					lifesteal_amt = 0;
	int					heal_amt = 0;
	int					armor_mit = 0;

	gold_gained = (((rand() % 25) + 1) * hunters) / ((gold_exponent + 1) * 10);
	gold += gold_gained;
	if (gold >= 1000000000)
	{
		gold_exponent++;
		gold /= 10;
	}
	if (fd <= 0)
		return (1);
	printf("%zu\n", equip.size());
	if (equip.size() > 0)
	{
		for (std::map<int, Item *>::iterator it = equip.begin(); it != equip.end(); ++it)
		{
			for (int i = 0; i != 5; i++)
			{
				printf("%d\n", it->second->enchants[i]);
				if (it->second->enchants[i] == PHYS_DMG)
					dmg += it->second->scale[i];
				else if (it->second->enchants[i] == STR)
					strbuff += it->second->scale[i];
				else if (it->second->enchants[i] == DEX)
					dexbuff += it->second->scale[i];
				else if (it->second->enchants[i] == INT)
					intbuff += it->second->scale[i];
				else if (it->second->enchants[i] == LIFESTEAL)
					lifesteal_amt += it->second->scale[i];
				else if (it->second->enchants[i] == HEAL)
					heal_amt += it->second->scale[i];
			}
			if (s->item_bases[it->second->base_id]->armor)
				armor_mit += s->item_bases[it->second->base_id]->armor;
			if (s->item_bases[it->second->base_id]->damage_min)
				dmg += (s->item_bases[it->second->base_id]->damage_min + (rand() % (s->item_bases[it->second->base_id]->damage_max - s->item_bases[it->second->base_id]->damage_min)));
		}
	}
	if (heal_amt)
		hp += heal_amt;
	if (rand() % (1000 - (dex + dexbuff) <= 0 ? 1 : 1000 - (dex + dexbuff)) == 0)
		dmg += dmg + (dex + dexbuff);
	if (mon.hp > 0 && fd > 0)
	{
		mon.hp -= dmg + ((str + strbuff) / 2);
		s->notify(this, string_format("You deal %d damage to the monsters!", dmg + ((str + strbuff) / 2)));
		hp -= (mon.dmg - (armor_mit / 20)) - lifesteal_amt;
	}
	else
	{
		mon.count = (rand() % 3) + 1;
		mon.hp = (10 * lvl) * 3;
		mon.level = lvl;
		mon.dmg = lvl * 2;
		return (2);
	}
	if (hp <= 0)
	{
		printf("%s died!\n", name);
		hp = max_hp;
		exp /= 2;
		mana = max_mana;
		return (3);
	}
	if (hp < max_hp)
		hp++;
	if (mana < max_mana)
		mana += intel + intbuff;
	if (hp > max_hp)
		hp = max_hp;
	return (1);
}
