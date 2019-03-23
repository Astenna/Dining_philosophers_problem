#include "../inc/philosopher.h"
#include <unistd.h>

bool philosopher::isStopped = false;

philosopher::philosopher(int _index, fork_t &_left_fork, fork_t &_right_fork) {
    left_fork = _left_fork;
    right_fork = _right_fork;
    index = _index;
    
    mt = std::mt19937(time(0));
    distribution = std::uniform_int_distribution<int>(1, 10);
}

void philosopher::dine() {
    std::cout << "Philsopher number " << index << " initialized." << std::endl;
    while(!isStopped) {
        eat();
        think();
    }
}

void philosopher::eat() {
    //std::cout << "Philsopher number " << index << " eats." << std::endl;
    int num = distribution(mt);
    std::cout << "Philsopher number " << index << " eats for " << num << std::endl;
    sleep(num);
}

void philosopher::think() {    
    //std::cout << "Philsopher number " << index << " sleeps." << std::endl;
    int num = distribution(mt);
    std::cout << "Philsopher number " << index << " sleeps for " << num << std::endl;
    sleep(num);
}