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

#include <list> // for the previous data (dps calculation)

# define WELCOME_MSG "Welcome to Hunters Online!\nThis is your main display port, where your various windows (inventory, auction house, etc.) will appear.\nIf you are confused, type 'help'.\nEnjoy the realm!\n"

enum	PlayerData
{
	DAMAGE = 0,
	EXP
};

namespace Hunters_Online
{
	class	PlayerAvg
	{
		public:
			PlayerAvg() {
				total_vals[0] = 0;
				total_vals[1] = 0;
			}
			~PlayerAvg() {
			}
			void	add_data(enum PlayerData type, int value)
			{
				int	tmp;
				if (type < 0 || type > EXP)
					return ;
				while(prev_data[type].size() > prev_data_max)
				{
					tmp = prev_data[type].back();
					prev_data[type].pop_back();
					total_vals[type] -= tmp;
				}
				prev_data[type].push_front(value);
				total_vals[type] += value;
			}
			int		get_avg(enum PlayerData type)
			{
				if (type < 0 || type > EXP)
					return (-1);
				if (total_vals[type] == 0 || prev_data[type].size() == 0)
					return (0);
				return (total_vals[type] / prev_data[type].size());
			}

		private:
			std::list<int>					prev_data[2];
			int								total_vals[2];
			int								prev_data_max = 10;
	};

	class	Screen
	{
		public:
			Screen();
			~Screen();

			void	createWindows(int lines, int cols);

			WINDOW	*display_box;
			WINDOW	*display;
			WINDOW	*console;
			WINDOW	*chat;
			WINDOW	*log_box;
			WINDOW	*log;
			WINDOW	*info;
			FIELD	*input[2];
			FORM	*form;
			int		update(PlayerAvg *plr, t_packet *p);
			int		state;
			int		last_state;
	};
}

void	scr_refresh(int sig);

#endif
