#include "../inc/visualization.h"
#include <unistd.h>

visualization::visualization() {
    initscr();
    noecho();
    box(stdscr,0,0);
    refresh();
    draw_philosophers();
    draw_forks();
}

void visualization::draw_philosophers() {
    calculate_coordinates();
    int column_width = (float)(separator-margin_x)/4;

    philosophers_window = derwin(stdscr,max_y-2*margin_y, separator-margin_x,margin_y,margin_x);
    box(philosophers_window,0,0);

    wprintw(philosophers_window,"Philosophers");

    mvwprintw(philosophers_window,2,2,"Id");
    mvwprintw(philosophers_window,2,column_width,"State");
    mvwprintw(philosophers_window,2,2*column_width,"Progress");
    mvwprintw(philosophers_window,2,3*column_width,"Dinners eaten");
    mvwhline(philosophers_window, 4, 1, 0 ,separator-margin_x-2);
    
    mvwvline(philosophers_window,1,column_width-2,0,max_y-2*margin_y-2);
    mvwvline(philosophers_window,1,2*column_width-2,0,max_y-2*margin_y-2);
    mvwvline(philosophers_window,1,3*column_width-2,0,max_y-2*margin_y-2);

    touchwin(philosophers_window);
    wrefresh(philosophers_window);
}

void visualization::draw_forks() {
    calculate_coordinates();
    int column_width = (float)(max_x-separator-margin_x)/3;
    forks_window = derwin(stdscr,max_y-2*margin_y, 3*column_width,margin_y,separator);

    box(forks_window,0,0);
    wprintw(forks_window,"Forks");

    mvwprintw(forks_window,2,2,"Id");
    mvwprintw(forks_window,2,column_width,"State");
    mvwprintw(forks_window,2,2*column_width,"Owner");

    mvwhline(forks_window, 4, 1, 0 ,max_x-separator-margin_x-2);
    mvwvline(forks_window,1,column_width-2,0,max_y-2*margin_y-2);
    mvwvline(forks_window,1,2*column_width-2,0,max_y-2*margin_y-2);

    touchwin(forks_window);
    wrefresh(forks_window);
}

void visualization::calculate_coordinates() {
    getmaxyx(stdscr, max_y, max_x);
    margin_x = 0.05 * (float) max_x;
    margin_y = 0.1 * (float) max_y;
    separator = (float) (max_x) * 0.6;
}

void visualization::print_fork_index(int index) {
    char buf[16];
    const char* p;
    sprintf(buf,"%d", index);
    p = buf; // need to cast from int to const char*

    std::lock_guard<std::mutex> lock(mutex);
    mvwprintw(forks_window, 2*index+5,3,"%s",p);
    touchwin(forks_window);
    wrefresh(forks_window);
}

void visualization::print_philosopher_index(int index) {
    char buf[16];
    const char* p;
    sprintf(buf,"%d", index);
    p = buf; // need to cast from int to const char*

    std::lock_guard<std::mutex> lock(mutex);
    mvwprintw(philosophers_window, 2*index+5,3,"%s",p);
    touchwin(philosophers_window);
    wrefresh(philosophers_window);
}

void visualization::update_fork_state(int index, std::string state) {
    int column_width = (float)(max_x-separator-margin_x)/3;
    std::lock_guard<std::mutex> lock(mutex);
    mvwprintw(forks_window, 2*index+5,column_width+3,"%s",state.c_str());
    touchwin(forks_window);
    wrefresh(forks_window);
}

void visualization::update_fork_owner(int index, int owner) {
    char buf[16];
    const char* p;
    sprintf(buf,"%d", owner);
    p = buf; // need to cast from int to const char*
    int  column_width = (float)(max_x-separator-margin_x)/3;

    std::lock_guard<std::mutex> lock(mutex);
    mvwprintw(forks_window, 2*index+5,2*column_width+3,"%s",p);
    touchwin(forks_window);
    wrefresh(forks_window);
}

void visualization::update_philosopher_state(int index, std::string state) {
int column_width = (float)(separator-margin_x)/4;
    std::lock_guard<std::mutex> lock(mutex);
    mvwprintw(philosophers_window, 2*index+5,column_width+3,"%s",state.c_str());
    touchwin(philosophers_window);
    wrefresh(philosophers_window);
}

visualization::~visualization() {
   delwin(forks_window);
   delwin(philosophers_window);
   endwin();
}
