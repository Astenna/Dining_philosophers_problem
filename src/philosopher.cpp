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
    std::cout << "Philsopher number " << index << " initialized." << std::endl;
    while(!isStopped) {
        eat();
        think();
    }
}

void philosopher::eat() {
    sleep(1);
    std::cout << "Philsopher number " << index << "  places left fork." << std::endl;
    left_fork.isOccupied = true;
    sleep(1);
    std::cout << "Philsopher number " << index << "  places right fork." << std::endl;
    right_fork.isOccupied = true;

    int num = distribution(mt);
    std::cout << "Philsopher number " << index << " eats for " << num 
                << "seconds." << std::endl;
    sleep(num);

    sleep(1);
    std::cout << "Philsopher number " << index << "  puts left fork." << std::endl;
    left_fork.isOccupied = false;
    sleep(1);
    std::cout << "Philsopher number " << index << "  puts right fork." << std::endl;
    right_fork.isOccupied = false;
}

void philosopher::think() {    
    int num = distribution(mt);
    std::cout << "Philsopher number " << index << " sleeps for " << num 
        << " seconds." << std::endl;
    sleep(num);
}