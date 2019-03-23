#include "../inc/fork.h"

class philosopher {

    fork left_fork;
    fork right_fork;

    void eat();
    void think();

    public:
    philosopher(fork &_left_fork, fork &_right_fork); 
    philosopher() {;}
    void dine();
};

