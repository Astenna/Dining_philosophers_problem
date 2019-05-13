#include "../inc/philosopher.h"

bool philosopher::is_stopped = false;
bool philosopher::is_started = false;

philosopher::philosopher(int _index, fork_t *_left_fork, fork_t *_right_fork) {
    left_fork = _left_fork;
    right_fork = _right_fork;
    id = _index;
    dinners_eaten = 0;
    mt = std::mt19937(time(0)+_index);
    distribution = std::uniform_int_distribution<int>(1, 3);
    state = philosopher_state::THINKING;
}

void philosopher::dine() {
    while(!is_started) {
        ;
    }
    while(!is_stopped) {
        eat();
        think();
    }
}

void philosopher::eat() {
    state = WAIT_LEFT;
    left_fork->take(id);
    state = WAIT_RIGHT;
    right_fork->take(id);
    
    state = philosopher_state::EATING;
    int num = distribution(mt);
    state = EATING;
    sleep(num);
    ++dinners_eaten;

    right_fork->put();
    left_fork->put();
}

void philosopher::think() {
    state = THINKING;
    state = philosopher_state::THINKING;
    int num = distribution(mt);
    sleep(num);
}

int philosopher::get_time_count() {
    return time_count;
}

int philosopher::get_dinners_eaten() {
    return dinners_eaten;
}

std::string philosopher::get_state() {
    switch(state) {
        case philosopher_state::EATING:
            return "eating           ";
        break;
        case philosopher_state::THINKING:
            return "thinking         ";
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