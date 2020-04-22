#ifndef PACKET_H
# define PACKET_H

typedef struct	s_packet
{
	char	id[16];
	char	command[16];
	char	data[30][16];
}				t_packet;

#endif
