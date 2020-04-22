#include "../includes/Server.hpp"

int	Player::tick()
{
	unsigned int		gold_gained = 0;
	unsigned int		sd = rand();

	for (int i = 0; i != hunters; i++)
	{
		sd = ((sd << 5) + sd) + i;
		gold_gained += sd % 25;
	}
	gold += gold_gained;
	if (mon.hp > 0 && fd > 0)
	{
		mon.hp -= (str / 2);
		hp -= mon.dmg;
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
		mana++;
	return (1);
}
