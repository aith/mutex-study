#pragma once

#include <atomic>
using namespace std;

#define MAX_THREADS 200

class mutex {
public:
    mutex() {
        // Empty on purpose
    }

    void init (int num_threads) {
        n = num_threads;
        for (int i = 0; i < num_threads; i++) {
            flags[i] = false;
            tickets[i] = 0;
        }
    }

    int get_next_ticket(){
        int highest = 0;
        for (int i = 0; i < n; i++){
            if (tickets[i] > highest) { highest = tickets[i]; }
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
            if (flags[i]  /* other thread wants to acquire */
            && lexicographic_lt(tickets[i], i, tickets[thread_id], thread_id)) { /* other thread comes first in line */
                return true;
            }
        }
        return false;
    }

    void lock(int thread_id) {
        int i = thread_id;
        flags[i] = true;
        tickets[i] = get_next_ticket();
        while(find_higher_priority_thread(thread_id)) {}
    }

    void unlock(int thread_id) {
        flags[thread_id] = false;
    }

private:
    int n;
    bool flags[MAX_THREADS];  // indexed by the thread id, whose element is their level
    int tickets[MAX_THREADS];
};
