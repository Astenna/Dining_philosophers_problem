#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#include "../inc/fork_t.h"
#include "../inc/visualization.h"
#include <random>
#include <iostream>

enum philosopher_state {
    EATING, THINKING, WAIT_LEFT, WAIT_RIGHT  
};

class philosopher {

    fork_t left_fork;
    fork_t right_fork;
    std::mt19937 mt;
    std::uniform_int_distribution<> distribution;

    void eat();
    void think();

    public:
    int index;
    philosopher_state state;
    static bool isStopped;
    static visualization *visualizer;
    
    std::string get_state();
    philosopher(int index, fork_t &_left_fork, fork_t &_right_fork); 
    philosopher() {;}
    int getId() { return index; }
    void dine();
};

#endif