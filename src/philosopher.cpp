#include "../inc/philosopher.h"
#include <unistd.h>

bool philosopher::isStopped = false;

philosopher::philosopher(int _index, fork_t &_left_fork, fork_t &_right_fork) {
    left_fork = _left_fork;
    right_fork = _right_fork;
    index = _index;
    mt = std::mt19937(time(0)+_index);
    distribution = std::uniform_int_distribution<int>(3, 6);
    visualizer->print_philosopher_index(index);
}

void philosopher::dine() {
    while(!isStopped) {
        eat();
        think();
    }
}

void philosopher::eat() {
    state = WAIT_LEFT;
    visualizer->update_philosopher_state(index,get_state());
    left_fork.request(index);

    state = WAIT_RIGHT;
    visualizer->update_philosopher_state(index,get_state());
    right_fork.request(index);

    std::lock(right_fork.get_mutex(), left_fork.get_mutex());                
    std::lock_guard<std::mutex> l1( right_fork.get_mutex(), std::adopt_lock );    
    std::lock_guard<std::mutex> l2( left_fork.get_mutex(), std::adopt_lock );

    state = EATING;
    visualizer->update_philosopher_state(index,get_state());
    int num = distribution(mt);
    sleep(num);

    state = THINKING;
    visualizer->update_philosopher_state(index,get_state());
    right_fork.free();
    left_fork.free();
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
            return "eating  ";
        break;
        case WAIT_LEFT:
            return "waiting \nfor left";
        break;
        case WAIT_RIGHT:
            return "waiting \nfor right";
        break;
        default:
            return "ERROR";
    }
}