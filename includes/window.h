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

namespace CurseWar
{
		class	Screen
		{
		public:
			Screen();
			~Screen();
			WINDOW	*console;
			WINDOW	*log;
			WINDOW	*display;
			WINDOW	*info;
			FIELD	*input[2];
			FORM	*form;
			int		update(t_packet *p);
		};
}

void	scr_refresh(int sig);

#endif
