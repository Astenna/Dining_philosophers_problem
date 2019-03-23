#include "philosopher.h"
#include "fork_t.h"
#include <thread>

class table {

    const int phil_num;
    std::thread* philospoherThreads;
    philosopher* philosophers;
    fork_t* forks;
    
    void initialize_philosphers();

    public:
    table(int _phil_num);
    ~table();
    void stop();
};