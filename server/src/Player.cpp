#include "../includes/Server.hpp"

Monster::Monster() { hp = 0; }

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
	int					max_hp_mod = 0;

	gold_gained = (((rand() % 25) + 1) * hunters) / ((gold_exponent + 1) * 10);
	gold += gold_gained;
	if (gold >= 1000000000)
	{
		gold_exponent++;
		gold /= 10;
	}
	if (fd <= 0)
		return (1);
	if (equip.size() > 0)
	{
		for (std::map<int, Item *>::iterator it = equip.begin(); it != equip.end(); ++it)
		{
			for (int i = 0; i != 5; i++)
			{
				printf("%d\n", s->auras[it->second->enchants[i]]->enchant);
				if (s->auras[it->second->enchants[i]]->enchant == PHYS_DMG)
					dmg += it->second->scale[i];
				else if (s->auras[it->second->enchants[i]]->enchant == STR)
					strbuff += it->second->scale[i];
				else if (s->auras[it->second->enchants[i]]->enchant == DEX)
					dexbuff += it->second->scale[i];
				else if (s->auras[it->second->enchants[i]]->enchant == INT)
					intbuff += it->second->scale[i];
				else if (s->auras[it->second->enchants[i]]->enchant == LIFESTEAL)
					lifesteal_amt += it->second->scale[i];
				else if (s->auras[it->second->enchants[i]]->enchant == HEAL)
					heal_amt += it->second->scale[i];
				else if (s->auras[it->second->enchants[i]]->enchant == HEALTH)
					max_hp_mod += it->second->scale[i];
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
	{
		s->notify(this, std::string("Critical hit!"), LOG);
		dmg += dmg + (dex + dexbuff);
	}
	if (mon.hp > 0 && fd > 0)
	{
		mon.hp -= dmg + ((str + strbuff) / 2);
		s->notify(this, string_format("You deal %d damage to the monsters!", dmg + ((str + strbuff) / 2)), LOG);
		hp -= (mon.dmg - (armor_mit / 20));
		s->notify(this, string_format("You take %d damage.", mon.dmg - (armor_mit / 20)), LOG);
		if (lifesteal_amt)
		{
			s->notify(this, string_format("You stole %d health.", lifesteal_amt), LOG);
			hp += lifesteal_amt;
		}
	}
	else
	{
		mon.count = (rand() % 3) + 1;
		mon.hp = ((10 * lvl) * mon.count) * 3;
		mon.level = lvl;
		mon.dmg = (lvl * 2) * mon.count;
		return (2);
	}
	if (hp <= 0)
	{
		printf("%s died!\n", name);
		hp = (max_hp + max_hp_mod);
		exp /= 2;
		mana = max_mana;
		return (3);
	}
	if (hp < (max_hp + max_hp_mod))
		hp++;
	if (mana < max_mana)
		mana += intel + intbuff;
	if (hp > (max_hp + max_hp_mod))
		hp = (max_hp + max_hp_mod);
	str += strbuff;
	dex += dexbuff;
	intel += intbuff;
	max_hp += max_hp_mod;
	s->sendStatus(this);
	str -= strbuff;
	dex -= dexbuff;
	intel -= intbuff;
	max_hp -= max_hp_mod;
	return (packet_queue->send(fd));
}

Player::Player()
{
	packet_queue = new PacketQueue();
}

Player::~Player()
{
	delete packet_queue;
}
