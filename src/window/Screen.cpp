#include "../../includes/window.h"

HeroShell::Screen	*mainscr;

HeroShell::Screen::Screen()
{
	int	r,c;

	initscr();
	raw();
	noecho();
	cbreak();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	curs_set(0);
	signal(SIGWINCH, scr_refresh);
	display = newwin(LINES * 0.75, COLS * 0.75, 0, 0);
	display_port = newwin((LINES * 0.75 - 2), (COLS * 0.75) - 2, 1, 1);
	console = newwin(LINES * 0.25, COLS, LINES * 0.75, 0);
	log = newwin((LINES * 0.25) - 2, COLS - 2, (LINES*0.75) + 1, 1);
	info = newwin(LINES * 0.75, COLS * 0.25, 0, COLS * 0.75);
	scrollok(log, TRUE);
	input[0] = new_field(1, COLS - 2, 1, 1, 0, 0);
	set_field_opts(input[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	input[1] = NULL;
	form = new_form(input);
	scale_form(form, &r, &c);
	set_form_win(form, console);
	set_form_sub(form, derwin(console, r, c, (LINES / 4) - 3, 0));
	post_form(form);

	form_driver(form, '>');
	box(display, ':', '*');
	box(console, ':', '*');
	box(info, ':', '*');
	refresh();
	wrefresh(display);
	wrefresh(display_port);
	wrefresh(console);
	wrefresh(info);
}

void	scr_refresh(int sig)
{
	int	r,c;
	char *buf;
	struct winsize w;

	endwin();
	initscr();
	raw();
	noecho();
	cbreak();
	ioctl(0, TIOCGWINSZ, &w);
	buf = field_buffer(mainscr->input[0], 0);
	delwin(mainscr->display);
	delwin(mainscr->console);
	delwin(mainscr->log);
	delwin(mainscr->info);
	unpost_form(mainscr->form);
	free_field(mainscr->input[0]);
	mainscr->display = newwin(w.ws_row * 0.75, w.ws_col * 0.75, 0, 0);
	mainscr->console = newwin(w.ws_row * 0.25, w.ws_col, w.ws_row * 0.75, 0);
	mainscr->log = newwin((w.ws_row * 0.25) - 2, w.ws_col - 2, (w.ws_row * 0.75) + 1, 1);
	mainscr->info = newwin(w.ws_row * 0.75, w.ws_col * 0.25, 0, w.ws_col * 0.75);
	scrollok(mainscr->log, TRUE);
	mainscr->input[0] = new_field(1, w.ws_col - 2, 1, 1, 0, 0);
	set_field_opts(mainscr->input[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	mainscr->input[1] = NULL;
	mainscr->form = new_form(mainscr->input);
	scale_form(mainscr->form, &r, &c);
	set_form_win(mainscr->form, mainscr->console);
	set_form_sub(mainscr->form, derwin(mainscr->console, r, c, (w.ws_row / 4) - 3, 0));
	post_form(mainscr->form);

	set_field_buffer(mainscr->input[0], 0, buf);
	box(mainscr->display, ':', '*');
	box(mainscr->console, ':', '*');
	box(mainscr->info, ':', '*');
	refresh();
	wrefresh(mainscr->display);
	wrefresh(mainscr->console);
	wrefresh(mainscr->info);
}

int	HeroShell::Screen::update(t_packet *pack)
{
	if (std::atoi(pack->data[12]) > 0)
		mvwprintw(info, 1, 1, "gold: %s * (10 ^ %s)     ", pack->data[0], pack->data[12]);
	else
		mvwprintw(info, 1, 1, "gold: %s     ", pack->data[0]);
	mvwprintw(info, 3, 1, "hunters: %s (%d g/s)     ", pack->data[1], std::atoi(pack->data[1]) * 25);
	mvwprintw(info, 4, 1, "str: %s     ", pack->data[2]);
	mvwprintw(info, 5, 1, "int: %s     ", pack->data[3]);
	mvwprintw(info, 6, 1, "dex: %s     ", pack->data[4]);
	mvwprintw(info, 7, 1, "hp: %s     ", pack->data[5]);
	mvwprintw(info, 8, 1, "mana: %s     ", pack->data[7]);
	mvwprintw(info, 9, 1, "lvl: %s     ", pack->data[10]);
	mvwprintw(info, 10, 1, "exp: %s     ", pack->data[11]);
	wrefresh(info);
	return (1);
}

HeroShell::Screen::~Screen()
{
	wborder(display, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wborder(console, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wborder(info, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(display);
	wrefresh(console);
	wrefresh(info);
	delwin(display);
	delwin(console);
	delwin(info);
	curs_set(1);
	endwin();
}
