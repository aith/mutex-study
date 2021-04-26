#pragma once

#include <atomic>
#include "stdio.h"
using namespace std;

#define MAX_THREADS 50

class mutex {
 public:
  mutex() {
    // Empty on purpose
  }
  
  void init (int num_threads) {
    n = num_threads;
    for (int i = 0; i < num_threads; i++) {
        levels[i] = 0;
        victims[i] = 0;
    }
  }

bool find_threads_at_gte_level(int thread_id) {
    for (int i=0; i< n; i++) {
        if (levels[i] >= levels[thread_id] && i != thread_id) { return true; }
    }
    return false;
}

  void lock(int thread_id) {
    int me = thread_id;
    for (int i = 1; i < n; i++) {
        levels[me] = i;
        victims[i] = me;
        while(n > 1  /* there exists other threads */
        && find_threads_at_gte_level(thread_id)  /*  there are threads with higher levels */
        && victims[i] == me) { /* spin */ }
    }
  }

  void unlock(int thread_id) {
    levels[thread_id] = 0;
  }

 private:
  int levels[MAX_THREADS];  // indexed by the thread id, whose element is their level
  int victims[MAX_THREADS];
  int n;
};
