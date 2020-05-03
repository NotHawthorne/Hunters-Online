#include "../includes/packet.h"

#include <stdio.h>
#include <unistd.h>

PacketQueue::PacketQueue()
{
	q = 0;
	tail = 0;
	is_empty = true;
	size = 0;
}

t_packet_header	*newHeader(char *id, int cmd, int amt)
{
	t_packet_header *h = new t_packet_header;
	bzero(h, sizeof(t_packet_header));
	memcpy(h->id, id, strlen(id));
	h->cmd = cmd;
	h->amt = amt;
	return (h);
}

int	PacketQueue::pushLoginResponse(bool success)
{
	t_packet_header	*h = newHeader("SERVER", success ? SERVER_LOGIN_SUCCESS : SERVER_LOGIN_FAIL, 0);
	push((void*)h, sizeof(t_packet_header));
	return (1);
}

int	PacketQueue::pushStatus(int g, int h, int str, int intel, int dex, int hp,
			int max_hp, int mana, int max_mana, int groupid, int lvl,
			int exp, int gold_exponent)
{
	t_status_packet *p = new t_status_packet;
	push((void*)newHeader("SERVER", SERVER_STATUS, 1), sizeof(t_packet_header));
	p->g = g;
	p->h = h;
	p->intel = intel;
	p->dex = dex;
	p->hp = hp;
	p->max_hp = max_hp;
	p->mana = mana;
	p->max_mana = max_mana;
	p->groupid = groupid;
	p->lvl = lvl;
	p->exp = exp;
	p->gold_exponent = gold_exponent;
	push((void*)p, sizeof(t_status_packet));
	return (1);
}

PacketQueue::~PacketQueue()
{
	Packet	*p = q;
	Packet	*tmp;

	while (p)
	{
		tmp = p->next;
		delete p->pack;
		delete p;
		p = tmp;
	}
}

int	PacketQueue::push(void *p, size_t size)
{
	if (!p)
		return (0);
	if (!is_empty)
	{
		tail->next = new Packet(p, size);
		tail = tail->next;
	}
	else
	{
		tail = new Packet(p, size);
		q = tail;
		is_empty = false;
	}
	/*if (size++ >= 51)
	{
		size--;
		delete pop();
	}*/
	return (1);
}

Packet	*PacketQueue::pop()
{
	Packet	*p;
	Packet	*ret;

	if (is_empty == true)
		return (0);
	ret = q;
	p = q->next;
	if (!p)
	{
		is_empty = true;
	}
	q = p;
	size--;
	return (ret);
}

int	PacketQueue::send(int fd)
{
	Packet	*tmp;
	bool	conn = true;
	int	i = 0;
	t_packet	*tmpack;

	while (tmp = pop())
	{
		if (conn && write(fd, tmp->pack, tmp->size) < 0)
			conn = false;
		delete tmp->pack;
		delete tmp;
	}
	return (conn);
}	

Packet::Packet(void *p, size_t sz) { pack = p; size = sz; next = 0; }
bool	PacketQueue::empty() { return (is_empty); };
void	*PacketQueue::front() { return (q->pack); }
