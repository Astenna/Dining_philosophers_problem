#include "../inc/table.h"
#include <iostream>

visualization *philosopher::visualizer;
visualization *fork_t::visualizer;

table::table(int _phil_num) : philosopher_number(_phil_num) {
    philospoher_threads = new std::thread[_phil_num];
    initialize_philosphers();
}

void table::initialize_philosphers() {

    visualizer = new visualization();
    philosopher::visualizer = visualizer;
    fork_t::visualizer = visualizer;

    forks.reserve(philosopher_number*2);
    for(int i=0; i < 2*philosopher_number; ++i) {
        forks.push_back(fork_t(i));
    }
    philosophers.reserve(philosopher_number);
    for(int i=0; i < philosopher_number; ++i) {
        philosophers.push_back(philosopher(i, std::ref(forks[2*i]),std::ref((forks[2*i+1]))));
        philospoher_threads[i] = std::thread(&philosopher::dine, std::ref(philosophers[i]));
    }
    //visualizer_thread = new std::thread(&visualization::visualize, std::ref(visualizer));
}

void table::stop() {
    philosopher::isStopped = true;
    for(int i=0; i < philosopher_number; ++i) {
        philospoher_threads[i].join();
    }
}

table::~table() {
    delete visualizer;
}
