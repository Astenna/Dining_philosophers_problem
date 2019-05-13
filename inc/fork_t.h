#ifndef FORK_T_H
#define FORK_T_H
#include <mutex>

class fork_t {
    private:
    std::mutex mutex;
    int id;
    int owner_id;
    bool is_taken;

    public:
    fork_t(int _id);
    int get_id();
    int get_owner_id();
    std::string get_is_taken_string();
    void take(int new_owner);
    void put();
};

#endif