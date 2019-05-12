#include "../inc/table.h"
#include <iostream>
#include <unistd.h>

table::table(int _phil_num) : philosopher_number(_phil_num) {
    philospoher_threads = new std::thread[_phil_num];
    initialize_visualization();
    initialize_threads();
}

void table::initialize_threads() {
    forks.reserve(philosopher_number);
    for(int i=0; i < philosopher_number; ++i) {
        forks.push_back(fork_t(i, ((i==0) ? 0 : i-1)));
    }

    philosophers.reserve(philosopher_number);
    for(int i=0; i < philosopher_number; ++i) {
        philosophers.push_back(philosopher(i, std::ref(forks[i]),std::ref((forks[(i+1)%philosopher_number]))));
        philospoher_threads[i] = std::thread(&philosopher::dine, std::ref(philosophers[i]));
    }
    visualizer_thread = new std::thread(&table::update_screen,this);
    philosopher::is_started= true;
}

void table::stop() {
    philosopher::is_stopped = true;
    for(int i=0; i < philosopher_number; ++i) {
        philospoher_threads[i].join();
    }
}

void table::initialize_visualization() {
    initscr();
    noecho();
    box(stdscr,0,0);
    refresh();

    getmaxyx(stdscr, max_y, max_x);
    margin_x = 0.05 * (float) max_x;
    margin_y = 0.1 * (float) max_y;
    separator = (float) (max_x) * 0.6;

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

    column_width = (float)(max_x-separator-margin_x)/3;
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

void table::update_philosophers() {
    int column_width = (float)(separator-margin_x)/4;
    char buf[16];
    const char* p;

    for(int i=0; i<philosopher_number; ++i) {
        //std::cout << std::endl << philosophers[i].get_state() <<std::endl;
        sprintf(buf,"%d", philosophers[i].get_id());
        p = buf;
        mvwprintw(philosophers_window, 2*i+5,3,"%s",p);
        mvwprintw(philosophers_window, 2*i+5,column_width+3,"%s",philosophers[i].get_state().c_str());
    }
    touchwin(philosophers_window);
    wrefresh(philosophers_window);
}

void table::update_forks(int j) {
    int  column_width = (float)(max_x-separator-margin_x)/3;
    char buf[16];
    const char* p;
    std::cout<<std::endl<<std::endl<<std::endl<<j<<std::endl;
    for(int i=0; i<philosopher_number; ++i) {
        mvwprintw(forks_window, 2*i+5,column_width+3,"%s",forks[i].get_state().c_str());
        sprintf(buf,"%d", forks[i].get_owner_id());
        p = buf;
        mvwprintw(forks_window, 2*i+5,2*column_width+3,"%s",p);
        sprintf(buf,"%d", forks[i].get_id());
        p = buf; // need to cast from int to const char*
        mvwprintw(forks_window, 2*i+5,3,"%s",p);
    }
    touchwin(forks_window);
    wrefresh(forks_window);
}

void table::update_screen() {
    int i = 0;
    while(!philosopher::is_stopped) {
        update_philosophers();
        update_forks(i);
        ++i;
        //sleep(1);
        refresh();
    }
}

table::~table() {
   delwin(forks_window);
   delwin(philosophers_window);
   endwin();
}
