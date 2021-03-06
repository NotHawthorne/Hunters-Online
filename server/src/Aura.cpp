#include "../includes/effect.h"

Aura::Aura(char **argv)
{
	id = std::atoi(argv[0]);
	enchant = std::atoi(argv[1]);
	val = std::atoi(argv[2]);
	proc_rate = std::atoi(argv[3]);
	tier = std::atoi(argv[4]);
}

// PROCESS AURAS IN LOOP

int		Aura::process(Player *p, Item *i, std::map<int, ItemBase*> *bases,
							t_combat_frame *cb_frame, int scale)
{
	int		stackdmg = 0;
	int		proc = 1;
	if (proc_rate && (rand() % 100) > proc_rate)
		return (1);
	int		tot = 0;
	switch (enchant)
	{
		case PHYS_DMG:
			cb_frame->dmg += (int)((val + ((p->dex / 100.0) * proc_rate)) * (scale / 100.0)) + 1;
			break ;
		case CRIT_CHANCE:
			cb_frame->crit = cb_frame->crit ? cb_frame->crit : rand() % ((val * (scale / 100)) - 2) == 0;
			break ;
		case STR:
			cb_frame->strbuff += (int)(val * (scale / 100.0)) + 1;
			break ;
		case INT:
			cb_frame->intbuff += (int)(val * (scale / 100.0)) + 1;
			break ;
		case DEX:
			cb_frame->dexbuff += (int)(val * (scale / 100.0)) + 1;
			break ;
		case STUN:
			cb_frame->next_tick += val;
			break ;
		case HEALTH:
			cb_frame->max_hp_mod += (int)(val * (scale / 100.0)) + 1;
			break ;
		case HEAL:
			cb_frame->heal_amt += (int)((val + p->intel) * (scale / 100.0)) + 1;
			if (proc_rate)
				proc = cb_frame->heal_amt;
			break ;
		case CHAIN_LIGHTNING:
			stackdmg = (int)((val + p->intel) * (scale / 100.0)) + 1;
			for (int i = 0; i != p->mon.count; i++)
			{
				tot += stackdmg;
				cb_frame->dmg += stackdmg;
				stackdmg /= 3;
			}
			if (proc_rate)
				proc = tot;
			break ;
		case LIFESTEAL:
			cb_frame->lifesteal_amt += (int)(val * (scale / 100.0)) + 1;
			break ;
	}
	return (proc);
}

int		Aura::proc(Player *p, Monster *m, int scale)
{
	int	res = rand() % 100;
	if (res < proc_rate || !proc_rate)
		return (0);
	switch (enchant)
	{
		case HEAL:
			p->hp += val + scale;
			break ;
		case PHYS_DMG:
			m->hp -= val + scale;
			break ;
		case LIFESTEAL:
			m->hp -= val + scale;
			p->hp += val + scale;
			break ;
	}
	return (1);
}

int		Aura::apply(Player *p, int scale)
{
	switch (enchant)
	{
		case INT:
			p->intel += val + scale;
			break ;
		case STR:
			p->str += val + scale;
			break ;
		case DEX:
			p->dex += val + scale;
			break ;
		case HEALTH:
			p->max_hp += val + scale;
			break ;
	}
	return (1);
}

int		Aura::remove(Player *p, int scale)
{
	switch (enchant)
	{
		case INT:
			p->intel -= val + scale;
			break ;
		case STR:
			p->str -= val + scale;
			break ;
		case DEX:
			p->dex -= val + scale;
			break ;
		case HEALTH:
			p->max_hp -= val + scale;
			if (p->hp > p->max_hp)
				p->hp = p->max_hp;
			break ;
	}
	return (1);
}
