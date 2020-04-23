#include "../../includes/login.h"

#define ctrl(x) ((x) * 0x1f)

LoginManager::LoginManager()
{
	int	r, c;
	initscr();
	cbreak();
	noecho();
	raw();
	curs_set(0);
	passfield = 0;
	mainwin = newwin(8, (COLS / 3) + 2, LINES / 3, COLS / 3);
	fields[0] = new_field(1, COLS / 3, 2, 1, 0, 0);
	fields[1] = new_field(1, COLS / 3, 4, 1, 0, 0);
	fields[2] = NULL;
	set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	set_field_opts(fields[1], O_VISIBLE | O_EDIT | O_ACTIVE | O_PUBLIC);
	login_form = new_form(fields);
	scale_form(login_form, &r, &c);
	set_form_win(login_form, mainwin);
	set_form_sub(login_form, derwin(mainwin, r, c, 1, 0));
	post_form(login_form);
	box(mainwin, 0, 0);
	mvwprintw(mainwin, 1, 1, "%-s", "-=HeroShell=Login=-");
	mvwprintw(mainwin, 2, 1, "username:");
	mvwprintw(mainwin, 4, 1, "pass:");
	refresh();
	wrefresh(mainwin);
}

LoginManager::~LoginManager()
{
	unpost_form(login_form);
	free_form(login_form);
	free_field(fields[1]);
	free_field(fields[2]);
	endwin();
}

int LoginManager::readInput()
{
	char	*userbuf = NULL;
	while (1)
	{
		int c = wgetch(mainwin);
		switch (c)
		{
			case ('\033'):
				wgetch(mainwin);
				switch (wgetch(mainwin))
				{
					case 'D':
						form_driver(login_form, REQ_PREV_CHAR);
						break ;
					case 'C':
						form_driver(login_form, REQ_NEXT_CHAR);
						break ;
					case KEY_BACKSPACE:
						form_driver(login_form, REQ_DEL_CHAR);
						if (passfield && pass.size())
							pass.erase(pass.size() - 1);
						break ;
					default:
						break ;
				}
				break ;
			case 4:
				return (0);
				break ;
			case ctrl('c'):
				return (0);
				break ;
			case 10:
				form_driver(login_form, REQ_VALIDATION);
				form_driver(login_form, REQ_NEXT_FIELD);
				userbuf = field_buffer(fields[0], 0);
				if (passfield && (!userbuf || userbuf[0] == ' ' || pass.size() <= 0 || pass.size() > 16))
				{
					mvwprintw(mainwin, 6, 1, "invalid login\n");
					pass.clear();
					set_field_buffer(fields[0], 0, "");
					set_field_buffer(fields[1], 0, "");
					passfield = 0;
					break ;
				}
				if (pass.size() > 0 && pass[0] != ' ')
					return (1);
				else
					passfield = 1;
				break ;
			case 127:
				form_driver(login_form, REQ_DEL_PREV);
				if (passfield && pass.size())
					pass.erase(pass.size() - 1);
				break ;
			default:
				form_driver(login_form, passfield ? '*' : c);
				if (passfield)
					pass += c;
				break ;
		}
		wrefresh(mainwin);
		refresh();
	}
}
