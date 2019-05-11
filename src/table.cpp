#include "../inc/table.h"
#include <iostream>

table::table(int _phil_num) : philosopher_number(_phil_num) {
    philospoher_threads = new std::thread[_phil_num];
    initialize_philosphers();
}

void table::initialize_philosphers() {
    forks.reserve(philosopher_number*2);
    for(int i=0; i < 2*philosopher_number; ++i) {
        forks.push_back(fork_t(i));
    }
    philosophers.reserve(philosopher_number);
    for(int i=0; i < philosopher_number; ++i) {
        philosophers.push_back(philosopher(i, std::ref(forks[2*i]),std::ref((forks[2*i+1]))));
        philospoher_threads[i] = std::thread(&philosopher::dine, std::ref(philosophers[i]));
    }
    visualizer = visualization(std::ref(philosophers), std::ref(forks), philosopher_number);
    //visualizer_thread = new std::thread(&visualization::visualize, std::ref(visualizer));
}

void table::stop() {
    philosopher::isStopped = true;
    //visualizer_thread->join();
    for(int i=0; i < philosopher_number; ++i) {
        philospoher_threads[i].join();
    }
}