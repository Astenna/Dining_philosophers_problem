#include "../inc/visualization.h"
#include <unistd.h>

visualization::visualization(std::vector<philosopher> &_phil, std::vector<fork_t> &_forks, int num) {
    philosophers = _phil;
    forks = _forks;
    philosopher_number = num;
    initscr();
    noecho();
    box(stdscr,0,0);
    refresh();
    draw_forks();
    draw_philosophers(); 
}

void visualization::draw_philosophers() {
    calculate_coordinates();
    column_width = (float)(separator-margin_x)/4;

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

void visualization::calculate_coordinates() {
    getmaxyx(stdscr, max_y, max_x);
    margin_x = 0.05 * (float) max_x;
    margin_y = 0.1 * (float) max_y;
    separator = (float) (max_x) * 0.6;
}

void visualization::update_forks() {
    calculate_coordinates();
    column_width = (float)(max_x-separator-margin_x)/3;
    // need to cast from int to const char*
    char buf[16];
    const char* p;

    for(int i=0; i< philosopher_number; ++i) {
        sprintf(buf,"%d", forks[i].get_id());
        p = buf;
        mvwprintw(forks_window, 2*i+5,3,"%s",p);
        mvwprintw(forks_window, 2*i+5,column_width+3,"c");
        mvwprintw(forks_window, 2*i+5,column_width+3,"%s",forks[i].get_state().c_str());
        sprintf(buf,"%d", forks[i].get_owner_id());
        sprintf(buf,"%d", 'b');        
        p = buf;
        mvwprintw(forks_window, 2*i+5,2*column_width+3,"%s",p);
    }
    touchwin(forks_window);
    wrefresh(forks_window);
}


void visualization::update_philosophers() {
    calculate_coordinates();
    column_width = (float)(separator-margin_x)/4;
    // need to cast from int to const char*
    char buf[16];
    const char* p;

   for(int i=0; i < philosopher_number; ++i) {
        sprintf(buf,"%d", philosophers[i].getId());
        p = buf;
        mvwprintw(philosophers_window, 2*i+5,3,"%s",p);
        mvwprintw(philosophers_window, 2*i+5,3+column_width,philosophers[i].get_state().c_str());
        //mvwprintw(philosophers_window, 2*i+5,3,"%s",p);
        //mvwaddstr(philosophers_window, 2*i+5,column_width+3,philosophers[0].get_state().c_str());
    }
    touchwin(philosophers_window);
    wrefresh(philosophers_window);
}


void visualization::visualize() {
   int i =0;
   philosophers[0].index =889;
   while(!philosopher::isStopped) {
       i++;
       sleep(1);
       update_philosophers();
       update_forks();
       refresh();
   }
   delwin(forks_window);
   delwin(philosophers_window);
   endwin();
}
