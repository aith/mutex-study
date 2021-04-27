#pragma once

#include <atomic>
#include <mutex>
#include <semaphore.h>
using namespace std;

class rw_mutex {
public:
    rw_mutex() {
        sem_i = sem_init(&wrt, 0, 0);
        ctrin.store(0);
        ctrout.store(0);
        wait.store(0);
    }

    ~rw_mutex() {
        sem_destroy(&wrt);
    }

    void lock_reader() {
        in.lock();
        atomic_fetch_add(&ctrin, 1);
        in.unlock();
    }

    void unlock_reader() {
        out.lock();
        atomic_fetch_add(&ctrout, 1);
        if (wait.load() == 1 && ctrin.load() == ctrout.load()) {
            sem_post(&wrt);
        }
        out.unlock();
    }

    void lock() { /* Writer lock*/
        in.lock();
        out.lock();
        if (ctrin.load() == ctrout.load()) {
            out.unlock();
        }
        else {
            wait.store(1);
            out.unlock();
            sem_wait(&wrt);
            wait.store(0);
        }
    }

    void unlock() {
        in.unlock();
    }

private:
    mutex in;
    mutex out;
    sem_t wrt;
    int sem_i;
    atomic_int ctrin;
    atomic_int ctrout;
    atomic_bool wait;
};
