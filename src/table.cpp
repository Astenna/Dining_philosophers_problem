#include "../inc/table.h"


table::table(int _phil_num) : phil_num(_phil_num) {
    philosophers = new philosopher[_phil_num];
    forks = new fork[2*_phil_num];
    ids = new pthread_t[_phil_num];
}

table::~table() {
    delete philosophers;
    delete forks;
    delete ids;
}

void table::start_dinner() {

    for(int i=0; i < phil_num; ++i) {
        philosophers[i] = philosopher(forks[i*2],forks[i*2+1]);

    }
}