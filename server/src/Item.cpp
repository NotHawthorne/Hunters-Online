#include "../includes/item.h"

ItemBase::ItemBase(char **argv)
{
	id = atoi(argv[0]);
	memcpy(name, argv[1], strlen(argv[1]));
	item_type = atoi(argv[2]);
	item_class = atoi(argv[3]);
	item_levreq = atoi(argv[4]);
	damage_min = atoi(argv[5]);
	damage_max = atoi(argv[6]);
	speed = atoi(argv[7]);
	armor = atoi(argv[8]);
	level = atoi(argv[9]);
	slot = atoi(argv[10]);
}

Item::Item(t_packet *pack)
{
	base_id = atoi(pack->data[0]);
	rarity = atoi(pack->data[1]);
	for (int i = 0; i != 5; i++)
	{
		enchants[i] = atoi(pack->data[i + 2]);
		scale[i] = atoi(pack->data[i + 7]);
	}
}
