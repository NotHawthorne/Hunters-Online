#include "../../includes/client.h"
#include "../../includes/packet.h"

Player::Player(t_packet *p)
{
	memcpy(name, p->id, 16);
	level = atoi(p->data[0]);
}
