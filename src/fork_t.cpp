#include "../inc/fork_t.h"
#include <iostream>
#include <unistd.h>
#include <functional>



fork_t::fork_t(int _index, int _owner_id) {
    id = _index;
    owner_id = _owner_id;
    state = DIRTY;
    state = fork_state::DIRTY;
}

fork_t::fork_t(const fork_t &f) : id(f.id), owner_id(f.owner_id),
                                state(f.state)
                                {}

std::string fork_t::get_state() {
    std::lock_guard<std::mutex> lock(usage_mutex);
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
    return id;
}
    
int fork_t::get_owner_id() {
    return owner_id;
}

void fork_t::request(int requesting_id) {
    while(owner_id != requesting_id) {
        if(state == fork_state::CLEAN) {
           // std::cout<<"Filozof " << requesting_id << " czeka na " << id << std::endl;
            std::unique_lock<std::mutex> lock(condition_mutex);
            condition.wait(lock);
           // std::cout<<"Filozof " << requesting_id << " BUDZI SIE w oczekiwaniu na " << id << std::endl;
        } else {
           // std::cout<<"Filozof " << requesting_id << " dostaje czysty " << id << std::endl;
            std::lock_guard<std::mutex> lock(usage_mutex);
            state = fork_state::CLEAN;
            owner_id = requesting_id;
        }
    }
}

void fork_t::use() {
    usage_mutex.lock();
}

void fork_t::put_down() {
    state = fork_state::DIRTY;
    usage_mutex.unlock();
    //std::cout<<"Widelec " << id << "zwolniony  i brudny"<<std::endl;
    std::unique_lock<std::mutex> lock(condition_mutex);
    condition.notify_all();
}

fork_t& fork_t::operator=(fork_t const &f) {
    if(this == &f) return *this; 
    id = f.id;
    owner_id = f.owner_id;
    state = f.state;
    return *this;
}