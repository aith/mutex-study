#pragma once

#include <atomic>
#include "stdio.h"
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
        levels[i].store(0);
        victims[i].store(0);
    }
  }

bool find_threads_at_gte_level(int thread_id) {
    for (int i=0; i< n; i++) {
        if (levels[i].load() >= levels[thread_id].load() && i != thread_id) { return true; }
    }
    return false;
}

  void lock(int thread_id) {
    int me = thread_id;
    for (int i = 1; i < n; i++) {
        levels[me].store(i);
        victims[i].store(me);
        while(find_threads_at_gte_level(thread_id)  /*  there are threads with higher levels */
        && victims[i].load() == me) { std::this_thread::yield(); }
    }
  }

  void unlock(int thread_id) {
    levels[thread_id].store(0);
  }

 private:
  atomic_int levels[MAX_THREADS];  // indexed by the thread id, whose element is their level
  atomic_int victims[MAX_THREADS];
  atomic_int n;
};
