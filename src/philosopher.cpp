#include "../inc/philosopher.h"
#include <unistd.h>

bool philosopher::is_stopped = false;
bool philosopher::is_started = false;

philosopher::philosopher(int _index, fork_t &_left_fork, fork_t &_right_fork) {
    left_fork = _left_fork;
    right_fork = _right_fork;
    id = _index;
    mt = std::mt19937(time(0)+_index);
    distribution = std::uniform_int_distribution<int>(1, 3);
}

void philosopher::dine() {
    while(!is_started) {
        ;
    }
    while(!is_stopped) {
        request_forks();
        eat();
        think();
        put_down_forks();
    }
}

void philosopher::request_forks() {
    state = philosopher_state::WAIT_LEFT;
    left_fork.request(id);
    state = philosopher_state::WAIT_RIGHT;
    right_fork.request(id);
}

void philosopher::put_down_forks() {
   //std::cout<<"Filozof " << id << " wysyla zadania " << std::endl;
    right_fork.put_down();
    left_fork.put_down();
}


void philosopher::eat() {
    state = philosopher_state::EATING;
    //std::cout << "phil " << id <<get_state() <<std::endl;
    left_fork.use();
    right_fork.use();
    int num = distribution(mt);
    //std::cout << "Philsopher " << id << " eats for " << num
    //           << "seconds." << std::endl;
}

void philosopher::think() {  
    state = philosopher_state::THINKING;
    int num = distribution(mt);
    // std::cout << "Philsopher number " << id << " sleeps for " << num
     //   << " seconds." << std::endl;
    sleep(num);
}

std::string philosopher::get_state() {
    switch(state) {
        case philosopher_state::EATING:
            return "eating  ";
        break;
        case philosopher_state::THINKING:
            return "thinking";
        break;
        case philosopher_state::WAIT_LEFT:
            return "waiting for left";
        break;
        case philosopher_state::WAIT_RIGHT:
            return "waiting for right";
        default:
            return "ERROR";
    }
}