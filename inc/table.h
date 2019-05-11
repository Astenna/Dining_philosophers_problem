#include "philosopher.h"
#include "fork_t.h"
#include "visualization.h"
#include <thread>
#include <vector>

class table {

    const int philosopher_number;
    std::thread* philospoher_threads;
    std::vector<philosopher> philosophers;
    std::vector<fork_t> forks;
    visualization *visualizer;
    std::thread* visualizer_thread;
    
    void initialize_philosphers();

    public:
    ~table();
    table(int _phil_num);
    void stop();
};