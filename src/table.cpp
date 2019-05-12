#include "../inc/table.h"
#include <iostream>

//visualization *philosopher::visualizer;
//visualization *fork_t::visualizer;

table::table(int _phil_num) : philosopher_number(_phil_num) {
    //is_initialized = false;
    philospoher_threads = new std::thread[_phil_num];
    initialize_philosphers();
}

void table::initialize_philosphers() {

    //visualizer = new visualization();
    //philosopher::visualizer = visualizer;
    //fork_t::visualizer = visualizer;

    forks.reserve(philosopher_number);
    for(int i=0; i < philosopher_number; ++i) {
        forks.push_back(fork_t(i, ((i==0) ? 0 : i-1)));
        int value = ((i==0) ? 0 : i-1);
    }
    philosophers.reserve(philosopher_number);
    for(int i=0; i < philosopher_number; ++i) {
        philosophers.push_back(philosopher(i, std::ref(forks[i]),std::ref((forks[(i+1)%philosopher_number]))));
        philospoher_threads[i] = std::thread(&philosopher::dine, std::ref(philosophers[i]));
    }
   /* is_initialized = true;
    std::unique_lock<std::mutex> lock(mutex);
    condition.notify_all();*/
}

void table::stop() {
    philosopher::is_stopped = true;
    for(int i=0; i < philosopher_number; ++i) {
        philospoher_threads[i].join();
    }
}

table::~table() {
    //delete visualizer;
}
