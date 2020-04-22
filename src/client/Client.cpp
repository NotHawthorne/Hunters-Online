#include "../../includes/client.h"

int	CurseWar::Client::sendPacket(char *id, char *command,
									char **data)
{
	t_packet	p;

	bzero(&p.id, 16);
	bzero(&p.command, 16);
	strncpy(p.id, id, strlen(id));
	strncpy(p.command, command, strlen(command));
	for (int i = 0; data && data[i]; i++)
		strncpy(p.data[i], data[i], strlen(data[i]));
	write(conn_fd, &p, sizeof(t_packet));
	fflush(0);
	return (1);
}

int	CurseWar::Client::sendChat(char *data, size_t len)
{
	t_packet	p;
	int			x = 1;
	int			y = 0;
	std::string	l;

	bzero(&p.id, 16);
	bzero(&p.command, 16);
	strncpy(p.id, name, strlen(name));
	strncpy(p.command, "CHAT\0", 5);
	l = std::to_string((int)len);
	strncpy(p.data[0], l.c_str(), l.size() + 1);
	for (int i = 0; i < (int)len && data[i] && x < 30; i += 15)
	{
		bzero(p.data[x], 16);
		memcpy(p.data[x++], data + i, len - i > 16 ? 15 : len - i);
	}
	bzero(p.data[x], 16);
	write(conn_fd, &p, sizeof(t_packet));
	fflush(0);
	return (1);
}

CurseWar::Client::Client(char *user, char *pass)
{
	int		ret;
	char	**data = new char*[30];
	std::string	pass_hash;
	std::hash<std::string>	hasher;

	printf("%s %s\n", user, pass);
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	ret = inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr);
	conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	int flags = fcntl(conn_fd, F_GETFL);
	fcntl(conn_fd, F_SETFL, flags | O_NONBLOCK);
	ret = connect(conn_fd, (struct sockaddr*)&server_addr,
					sizeof(server_addr));
	printf("%d\n", ret);
	if (errno)
		printf("%s\n", strerror(errno));
	data[0] = new char[16];
	data[1] = NULL;
	size_t res = hasher(std::string(pass));
	pass_hash = std::to_string(res);
	strncpy(data[0], pass_hash.c_str(), pass_hash.size() > 16 ? 16 : pass_hash.size());
	data[0][pass_hash.size() > 16 ? 15 : pass_hash.size() - 2] = 0;
	printf("done\n");
	bzero(name, 16);
	memcpy(name, user, strlen(user) >= 16 ? 15 : strlen(user));
	sendPacket(user, "REQ_LOGIN", data);
}

CurseWar::Client::~Client()
{
	printf("dead\n");
}
