#ifndef VISUALIZATION_H
#define VISUALIZATION_H
#include <ncurses.h>
#include <mutex>

class visualization {
    private:
    WINDOW* philosophers_window;
    WINDOW* forks_window;
    std::mutex mutex;
    int max_x;
    int max_y;
    int margin_x;
    int margin_y;
    int separator;

    void draw_philosophers();
    void draw_forks();
    void calculate_coordinates();

    public:
    visualization();
    ~visualization();
    void print_fork_index(int index); 
    void print_philosopher_index(int index);
    void update_fork_state(int index, std::string state);
    void update_fork_owner(int index, int owner);
    void update_philosopher_state(int index, std::string state);

};

#endif