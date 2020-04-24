#ifndef PACKET_H
# define PACKET_H

# include <cstddef>

typedef struct	s_packet
{
	char	id[16];
	char	command[16];
	char	data[30][16];
}				t_packet;

class	Packet
{
public:
	t_packet	*pack;
	Packet		*next;
	Packet(t_packet *p);
};

class	PacketQueue
{
private:
	Packet	*q;
	Packet	*tail;
	bool	is_empty;
	size_t	size;
public:
	PacketQueue();
	~PacketQueue();
	int		push(t_packet *p);
	bool	empty();
	t_packet	*pop();
	t_packet	*front();
	int		send(int fd);
};

#endif
