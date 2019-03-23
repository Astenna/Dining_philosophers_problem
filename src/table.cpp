#include "../inc/table.h"
#include <iostream>

table::table(int _phil_num) : phil_num(_phil_num) {
    philosophers = new philosopher[_phil_num];
    forks = new fork_t[2*_phil_num];
    philospoherThreads = new std::thread[_phil_num];
    initialize_philosphers();
}

// what with philosopherThreads?, for now memory leak
table::~table() {
    delete philosophers;
    delete forks;
}

void table::initialize_philosphers() {

    for(int i=0; i < phil_num; ++i) {
        philosophers[i] = philosopher(i, forks[i*2],forks[i*2+1]);
        philospoherThreads[i] = std::thread(&philosopher::dine, &philosophers[i]);
        //philospoherThreads[i].join();
    }

        for(int i=0; i < phil_num; ++i) {
        //philosophers[i] = philosopher(i, forks[i*2],forks[i*2+1]);
        //philospoherThreads[i] = std::thread(&philosopher::dine, &philosophers[i]);
        philospoherThreads[i].join();
    }
}

void table::stop() {
    philosopher::isStopped = true;
}