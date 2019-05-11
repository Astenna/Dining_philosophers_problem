#include "../inc/philosopher.h"
#include <unistd.h>

bool philosopher::isStopped = false;

philosopher::philosopher(int _index, fork_t &_left_fork, fork_t &_right_fork) {
    left_fork = _left_fork;
    right_fork = _right_fork;
    index = _index;
    mt = std::mt19937(time(0)+_index);
    distribution = std::uniform_int_distribution<int>(1, 5);
}

void philosopher::dine() {
    index = 678;
    while(!isStopped) {
        state = WAIT_LEFT;
        eat();
        state = THINKING;
        think();
        if(index == 889) {
            exit(0);
        }
    }
}

void philosopher::eat() {
    sleep(1);
    left_fork.isOccupied = true;
    sleep(1);
    right_fork.isOccupied = true;

    int num = distribution(mt);
    sleep(num);

    sleep(1);
    left_fork.isOccupied = false;
    sleep(1);
    right_fork.isOccupied = false;
}

void philosopher::think() {    
    int num = distribution(mt);
    sleep(num);
}

std::string philosopher::get_state() {
    switch(state) {

        case THINKING:
            return "thinking";
        break;
        case EATING:
            return "eating";
        break;
        case WAIT_LEFT:
            return "waiting for left";
        break;
        case WAIT_RIGHT:
            return "waiting for right";
        break;
        default:
            return "ERR";
    }
}