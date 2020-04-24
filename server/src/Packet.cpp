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

int	PacketQueue::push(t_packet *p)
{
	if (!p)
		return (0);
	if (!is_empty)
	{
		tail->next = new Packet(p);
		tail = tail->next;
	}
	else
	{
		tail = new Packet(p);
		q = tail;
		is_empty = false;
	}
	size++;
	return (1);
}

t_packet	*PacketQueue::pop()
{
	Packet	*p;
	t_packet *pa;

	if (is_empty == true)
		return (0);
	p = q->next;
	pa = q->pack;
	delete q;
	if (!p)
	{
		is_empty = true;
	}
	q = p;
	size--;
	return (pa);
}

int	PacketQueue::send(int fd)
{
	Packet	*tmp;
	bool	conn = true;
	int	i = 0;
	t_packet	*tmpack;

	while (tmpack = pop())
	{
		if (conn && write(fd, &(*tmpack), sizeof(t_packet)) < 0)
			conn = false;
		delete tmpack;
	}
	return (conn);
}	

Packet::Packet(t_packet *p) { pack = p; next = 0; }
bool	PacketQueue::empty() { return (is_empty); };
t_packet	*PacketQueue::front() { return (q->pack); }
