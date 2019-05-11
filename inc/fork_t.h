#ifndef FORK_T_H
#define FORK_T_H
#include <mutex>
#include <condition_variable>
#include "../inc/visualization.h"

enum fork_state {
    CLEAN, DIRTY
};

class fork_t {
    int index;
    int owner_id;
    fork_state state;
    mutable std::mutex mutex;
    std::condition_variable condition;
    
    public:
    fork_t() { ; }
    fork_t(int _index,int _owner_id);
    fork_t(const fork_t &f);
    static visualization *visualizer;

    void request(int phil_req);
    void free();
    static bool is_initialized;
    std::string get_state();
    std::mutex &get_mutex() { return mutex; }
    int get_id();
    int get_owner_id();
    fork_t& operator=(fork_t const &f);
};

#endif