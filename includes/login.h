#ifndef LOGIN_H
# define LOGIN_H

#include <form.h>
#include <curses.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

class	LoginManager
{
public:
	FIELD	*fields[3];
	FORM	*login_form;
	WINDOW	*mainwin;
	int		passfield;
	std::string	pass;

	LoginManager();
	~LoginManager();
	int readInput();
	int	attemptLogin(int fd, char *user, char *pass);
};

#endif
