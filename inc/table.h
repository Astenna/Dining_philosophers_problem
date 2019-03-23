#include "philosopher.h"
#include "fork.h"
#include <pthread.h>

class table {

    const int phil_num;
    pthread_t* ids;
    philosopher* philosophers;
    fork* forks;

    ~table();
    
    public:
    table(int _phil_num);
    void start_dinner();
};