#ifndef FORK_T_H
#define FORK_T_H
#include "../inc/visualization.h"

enum fork_state {
    CLEAN, DIRTY
};

class fork_t {
    int index;
    int owner_id;
    
    public:
    fork_state state; // make private later
    fork_t() { ; }
    fork_t(int _index);
    bool isOccupied;
    static visualization *visualizer;

    std::string get_state();
    int get_id();
    int get_owner_id();
};

#endif