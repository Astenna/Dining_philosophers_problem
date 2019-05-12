#ifndef FORK_T_H
#define FORK_T_H
#include <mutex>
#include <condition_variable>
#include <atomic>

enum fork_state {
    CLEAN, DIRTY
};

class fork_t {
    int id;
    int owner_id;
    fork_state state;
    std::mutex condition_mutex;
    std::mutex usage_mutex;
    std::condition_variable condition;
    
    public:
    fork_t() { ; }
    fork_t(int _id,int _owner_id);
    fork_t(const fork_t &f);
    fork_t& operator=(fork_t const &f);

    void request(int requesting_id);
    void use();
    void put_down();

    std::string get_state();
    int get_id();
    int get_owner_id();
};

#endif