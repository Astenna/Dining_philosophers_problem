#include "../inc/fork_t.h"
#include <iostream>
#include <unistd.h>
bool fork_t::is_initialized = false;

fork_t::fork_t(int _index, int _owner_id) {
    index = _index;
    owner_id = _owner_id;
    state = DIRTY;
    visualizer->print_fork_index(_index);
}

fork_t::fork_t(const fork_t &f) : index(f.index), owner_id(f.owner_id),
                                state(f.state)
                                {}

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

void fork_t::request(int phil_req) {
    while (owner_id != phil_req ) {
        std::unique_lock<std::mutex> lck(mutex);
        while (state == CLEAN && is_initialized)  {
            condition.wait(lck);
        } 
        state = CLEAN;
        owner_id = phil_req;
        visualizer->update_fork_state(index,get_state());
        visualizer->update_fork_owner(index,phil_req);
        std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<"lock on "<< index << "by " << phil_req;
        while(true);
    }
}

void fork_t::free() {
    state = DIRTY;
    visualizer->update_fork_state(index, get_state());
    condition.notify_all();
}

fork_t& fork_t::operator=(fork_t const &f) {
    if(this == &f) return *this; 
    std::lock(mutex, f.mutex);                
    std::lock_guard<std::mutex> l1( mutex, std::adopt_lock );    
    std::lock_guard<std::mutex> l2( f.mutex, std::adopt_lock );
    index = f.index;
    owner_id = f.owner_id;
    state = f.state;
    return *this;
}