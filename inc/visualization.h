#ifndef VISUALIZATION
#define VISUALIZATION
#include <ncurses.h>
#include "philosopher.h"
#include "fork_t.h"

class visualization {
    private:
    int philosopher_number;
    std::vector<philosopher> philosophers;
    std::vector<fork_t> forks;
    WINDOW* philosophers_window;
    WINDOW* forks_window;
    int max_x;
    int max_y;
    int margin_x;
    int margin_y;
    int separator;
    int column_width;

    void calculate_coordinates();

    public:
    visualization() {;}
    visualization(std::vector<philosopher> &_philosophers, std::vector<fork_t> &_forks, int num);
    void draw_philosophers();
    void draw_forks();
    void update_philosophers();
    void update_forks();
    void visualize();
};

#endif