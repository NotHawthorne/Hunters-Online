#include "../includes/Server.hpp"

Monster::Monster() { hp = 0; }

int	Player::tick(Server *s)
{
	unsigned int		gold_gained = 0;
	int					dmg = 0;
	int					armor_mit = 0;
	int					dead = 0;
	int					kill = 0;

	if (fr == NULL)
	{
		fr = new t_combat_frame;
		bzero(fr, sizeof(t_combat_frame));
	}
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
			for (int i = 0; i != 5 && it->second->enchants[i]; i++)
			{
				int ret = 0;
				if ((ret = s->auras[it->second->enchants[i]]->process(this, it->second, &s->item_bases, fr, it->second->scale[i])) > 1)
				{
					switch (s->auras[it->second->enchants[i]]->enchant)
					{
						case CHAIN_LIGHTNING:
							s->notify(this, string_format("Chain lightning strikes your enemies for %d damage!", ret), LOG);
							break ;
						case HEAL:
							s->notify(this, string_format("You are healed for %d!", ret), LOG);
							break ;
					}
				}
				/*
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
				*/
			}
			if (s->item_bases[it->second->base_id]->armor)
				fr->armor_mit += s->item_bases[it->second->base_id]->armor;
			if (s->item_bases[it->second->base_id]->damage_min)
				fr->dmg += (s->item_bases[it->second->base_id]->damage_min + (rand() % (s->item_bases[it->second->base_id]->damage_max - s->item_bases[it->second->base_id]->damage_min)));
		}
	}
	if (fr->heal_amt)
		hp += fr->heal_amt;
	if (rand() % (1000 - (dex + fr->dexbuff) <= 0 ? 1 : 1000 - (dex + fr->dexbuff)) == 0 || fr->crit)
	{
		s->notify(this, std::string("Critical hit!"), LOG);
		fr->dmg += fr->dmg + (dex + fr->dexbuff);
	}
	if (mon.hp > 0 && fd > 0)
	{
		mon.hp -= fr->dmg + ((str + fr->strbuff) / 2);
		s->notify(this, string_format("You deal %d damage to the monsters! (%d / %d)", fr->dmg + ((str + fr->strbuff) / 2)), mon.hp, mon.max_hp, LOG);
		hp -= (mon.dmg - (armor_mit / 20));
		s->notify(this, string_format("You take %d damage.", mon.dmg - (armor_mit / 20)), LOG);
		if (fr->lifesteal_amt)
		{
			s->notify(this, string_format("You stole %d health.", fr->lifesteal_amt), LOG);
			hp += fr->lifesteal_amt;
		}
	}
	else
	{
		mon.count = (rand() % 3) + 1;
		mon.hp = ((10 * lvl) * mon.count) * 3;
		mon.max_hp = mon.hp;
		mon.level = lvl;
		mon.dmg = (lvl * 2) * mon.count;
		kill = 1;
		s->notify(this, string_format("You are attacked by %d monsters! (%d / %d)", mon.count, mon.hp, mon.max_hp), LOG);
	}
	if (hp <= 0)
	{
		printf("%s died!\n", name);
		hp = (max_hp + fr->max_hp_mod);
		exp /= 2;
		mana = max_mana;
		dead = 1;
	}
	if (hp < (max_hp + fr->max_hp_mod))
		hp++;
	if (mana < max_mana)
		mana += (intel + fr->intbuff);
	if (hp > (max_hp + fr->max_hp_mod))
		hp = (max_hp + fr->max_hp_mod);
	str += fr->strbuff;
	dex += fr->dexbuff;
	intel += fr->intbuff;
	max_hp += fr->max_hp_mod;
	s->sendStatus(this);
	str -= fr->strbuff;
	dex -= fr->dexbuff;
	intel -= fr->intbuff;
	max_hp -= fr->max_hp_mod;
	fr->dmg = 0;
	fr->strbuff = 0;
	fr->dexbuff = 0;
	fr->intbuff = 0;
	fr->lifesteal_amt = 0;
	fr->heal_amt = 0;
	fr->armor_mit = 0;
	fr->max_hp_mod = 0;
	fr->crit = 0;
	fr->next_tick = fr->next_tick ? fr->next_tick - 1 : 0;
	fr->armor_mit = 0;
	int ret = packet_queue->send(fd);
	if (dead || kill)
		return (dead ? 3 : 2);
	return (ret);
}

Player::Player()
{
	packet_queue = new PacketQueue();
	fr = NULL;
	access = 0;
}

Player::~Player()
{
	delete packet_queue;
}
