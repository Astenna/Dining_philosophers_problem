#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H
#include "../inc/fork_t.h"
#include <random>
#include <iostream>

enum philosopher_state {
    EATING, THINKING, WAIT_LEFT, WAIT_RIGHT  
};

class philosopher {
    philosopher_state state;
    fork_t left_fork;
    fork_t right_fork;
    std::mt19937 mt;
    std::uniform_int_distribution<> distribution;

    void eat();
    void think();
    void request_forks();
    void put_down_forks();

    public:
    int id;

    philosopher(int id, fork_t &_left_fork, fork_t &_right_fork); 
    philosopher() {;}
    static bool is_stopped;
    static bool is_started;
    std::string get_state();
    int get_id() { return id; }
    void dine();
};

#endif