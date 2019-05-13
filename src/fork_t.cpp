#include "../inc/fork_t.h"

fork_t::fork_t(int _id) {
    id = _id;
}

int fork_t::get_id() {
    return id;
}

int fork_t::get_owner_id() {
    return owner_id;
}

std::string fork_t::get_is_taken_string() {
    if(is_taken) {
        return "occupied ";
    } else {
        return "available";
    }
}

void fork_t::take(int new_owner) {
    mutex.lock();
    owner_id = new_owner;
    is_taken = true;
}

void fork_t::put() {
    is_taken = false;
    mutex.unlock();
}