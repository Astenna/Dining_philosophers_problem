#ifndef FORK_T_H
#define FORK_T_H
#include "string"

enum fork_state {
    CLEAN, DIRTY
};

class fork_t {
    int index;
    fork_state state;
    int owner_id;
    
    public:
    
    fork_t() { ; }
    fork_t(int _index);
    bool isOccupied;

    std::string get_state();
    int get_id();
    int get_owner_id();
};

#endif