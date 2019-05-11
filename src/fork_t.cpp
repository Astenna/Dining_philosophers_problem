#include "../inc/fork_t.h"

fork_t::fork_t(int _index) {
    index = _index;
    state = DIRTY;
    visualizer->print_fork_index(_index);
}

std::string fork_t::get_state() {
    switch(state) {
        case CLEAN:
            return "clean";
        case DIRTY:
            return "dirty";
        default:
            return "ERROR";
    }
}
    
int fork_t::get_id() {
    return index;
}
    
int fork_t::get_owner_id() {
    return owner_id;
}