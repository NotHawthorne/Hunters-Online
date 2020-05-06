#ifndef PACKET_H
# define PACKET_H

# include <cstddef>
# include <string.h>
# include <sys/socket.h>

enum	Log_Levels
{
	SYSTEM = 0,
	LOG = 1,
	NOTIFY = 2
};

enum	client_packet_types
{
	CLIENT_LOGIN,
	CLIENT_CHAT,
	CLIENT_ITEMS,
	CLIENT_PLAYERS,
	CLIENT_EQUIP,
	CLIENT_DROP,
	CLIENT_GIVE,
	CLIENT_LIST,
	CLIENT_SKILLS
};

enum	server_packet_types
{
	SERVER_LOGIN_FAIL,
	SERVER_LOGIN_SUCCESS,
	SERVER_NOTIFY,
	SERVER_CHAT,
	SERVER_STATUS,
	SERVER_CHARACTERS
};

typedef struct	s_packet
{
	char	id[16];
	char	command[16];
	char	data[30][16];
}				t_packet;

typedef struct	s_packet_header
{
	char	id[16];
	int	cmd;
	int	amt;
}		t_packet_header;

typedef struct	s_login_packet
{
	char	pass[16];
}		t_login_packet;

typedef struct	s_chat_packet
{
	char	dest[16];
	char	data[240];
}		t_chat_packet;

typedef struct	s_inven_cmd_packet
{
	int	item_id;
	int	cmd;
	char	dest[16];
}		t_inven_cmd_packet;

typedef struct	s_status_packet
{
	int	g;
	int	h;
	int	str;
	int	intel;
	int	dex;
	int	hp;
	int	max_hp;
	int	mana;
	int	max_mana;
	int	groupid;
	int	lvl;
	int	exp;
	int	gold_exponent;
}		t_status_packet;

typedef struct	s_character_packet
{
	char	name[16];
	int	pclass;
	int	race;
	int	level;
	int	hp;
	int	max_hp;
	int	mana;
	int	max_mana;
}		t_character_packet;

class	Packet
{
public:
	void		*pack;
	size_t		size;
	Packet		*next;
	Packet(void *p, size_t size);
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
	int		push(void *p, size_t size);
	int		pushLoginResponse(bool success, int amt);
	int		pushStatus(int g, int h, int str,
					int intel, int dex, int hp,
					int max_hp, int mana, int max_mana,
					int groupid, int lvl, int exp,
					int gold_exponent);
	bool	empty();
	Packet		*pop();
	void		*front();
	int		sendData(int fd);
};

#endif
