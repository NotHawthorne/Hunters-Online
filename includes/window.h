#ifndef WINDOW_H
# define WINDOW_H

#include <ncurses.h>
#include <form.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "packet.h"

# define WELCOME_MSG "Welcome to HeroShell!\nThis is your main display port, where your various windows (inventory, auction house, etc.) will appear.\nIf you are confused, type 'help'.\nEnjoy the realm!\n"

namespace HeroShell
{
		class	Screen
		{
		public:
			Screen();
			~Screen();
			WINDOW	*console;
			WINDOW	*log;
			WINDOW	*display;
			WINDOW	*display_port;
			WINDOW	*info;
			FIELD	*input[2];
			FORM	*form;
			int		update(t_packet *p);
			int		state;
			int		last_state;
		};
}

void	scr_refresh(int sig);

#endif
