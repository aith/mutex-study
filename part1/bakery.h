#pragma once

#include <atomic>
using namespace std;

#define MAX_THREADS 128

class mutex {
public:
    mutex() {
        // Empty on purpose
    }

    void init (int num_threads) {
        n.store(num_threads);
        for (int i = 0; i < num_threads; i++) {
            flags[i].store(false);
            tickets[i].store(0);
        }
    }

    int get_next_ticket(){
        int highest = 0;
        for (int i = 0; i < n; i++){
            if (tickets[i].load() > highest) { highest = tickets[i].load(); }
        }
        return highest + 1;
    }

    bool lexicographic_lt(int label1, int tid1, int label2, int tid2) {
        if (label1 < label2 || (label1 == label2 && tid1 < tid2)) return true;
        return false;
    }

    bool find_higher_priority_thread(int thread_id) {
        for (int i = 0; i < n; i++) {
            if (i == thread_id) { continue; }
            if (flags[i].load()  /* other thread wants to acquire */
            && lexicographic_lt(tickets[i].load(), i, tickets[thread_id].load(), thread_id)) { /* other thread comes first in line */
                return true;
            }
        }
        return false;
    }

    void lock(int thread_id) {
        int i = thread_id;
        flags[i].store(true);
        tickets[i].store(get_next_ticket());
        while(find_higher_priority_thread(thread_id)) { std::this_thread::yield(); }
    }

    void unlock(int thread_id) {
        flags[thread_id].store(false);
    }

private:
    atomic_int n;
    atomic_bool flags[MAX_THREADS];  // indexed by the thread id, whose element is their level
    atomic_int tickets[MAX_THREADS];
};
