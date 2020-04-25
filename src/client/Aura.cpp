#include "../../includes/effect.h"

Aura::Aura(char **argv)
{
	id = std::atoi(argv[0]);
	enchant = std::atoi(argv[1]);
	val = std::atoi(argv[2]);
	proc_rate = std::atoi(argv[3]);
	tier = std::atoi(argv[4]);
	memcpy(title, argv[5], strlen(argv[5]) + 1);
	pre = std::atoi(argv[6]);
}
