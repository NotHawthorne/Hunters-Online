#include "../includes/effect.h"

Aura::Aura(char **argv)
{
	id = std::atoi(argv[0]);
	enchant = std::atoi(argv[1]);
	val = std::atoi(argv[2]);
	proc_rate = std::atoi(argv[3]);
	tier = std::atoi(argv[4]);
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
