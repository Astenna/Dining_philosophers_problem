#include "philosopher.h"
#include "fork_t.h"
#include <ncurses.h>
#include <thread>
#include <vector>

class table {

    const int philosopher_number;
    std::thread* philospoher_threads;
    std::vector<philosopher> philosophers;
    std::vector<fork_t> forks;

    std::thread* visualizer_thread;
    WINDOW* philosophers_window;
    WINDOW* forks_window;
    int max_x;
    int max_y;
    int margin_x;
    int margin_y;
    int separator;
    void update_forks(int j);
    void update_philosophers();
    void update_screen();
    void initialize_visualization();
    void initialize_threads();

    public:
    bool is_initialized;
    ~table();
    table(int _phil_num);
    void stop();
};