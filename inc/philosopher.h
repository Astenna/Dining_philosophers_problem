#include "../inc/fork_t.h"
#include <random>
#include <iostream>

class philosopher {

    int index;
    fork_t left_fork;
    fork_t right_fork;

    std::mt19937 mt;
    std::uniform_int_distribution<> distribution;

    void eat();
    void think();

    public:
    static bool isStopped;
    philosopher(int index, fork_t &_left_fork, fork_t &_right_fork); 
    philosopher() {;}
    void dine();
};

