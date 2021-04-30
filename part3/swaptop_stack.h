#include <shared_mutex>

using namespace std;

class Llist_node {
public:
    Llist_node(int d) {
        data = d;
        next = NULL;
    }

    int data;
    Llist_node *next;
};

class CSE113_Stack {
public:

    CSE113_Stack() {
        start = NULL;
    }

    int pop() {
        lock.lock();

        if (start == NULL) {
            lock.unlock();
            return -1;
        }

        if (start->next == NULL) {
            int ret = start->data;
            delete start;
            start = NULL;
            lock.unlock();
            return ret;
        }

        Llist_node *current = start->next;
        Llist_node *previous = start;
        while (current->next != NULL) {
            previous = current;
            current = current->next;
        }

        int ret = current->data;
        previous->next = NULL;
        delete current;

        lock.unlock();

        return ret;
    }


    int peek() {
        lock.lock_shared();

        if (start == NULL) {
            lock.unlock_shared();
            return -1;
        }

        Llist_node *current = start;
        while (current->next != NULL) {
            current = current->next;
        }
        int d = current->data;
        lock.unlock_shared();
        return d;
    }

    void push(int p) {
        lock.lock();

        if (start == NULL) {
            start = new Llist_node(p);
            lock.unlock();
            return;
        }

        Llist_node *current = start;
        /* push to top */
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new Llist_node(p);
        lock.unlock();
    }

    void swaptop(int to_swap) {
        lock.lock_shared();

        if (start == NULL) {
            lock.unlock_shared();
            lock.lock();
            start = new Llist_node(to_swap);
            lock.unlock();
            return;
        }

        Llist_node *current = start;
        while (current->next != NULL) {
            current = current->next;
        }

       int top_val = current->data;
       if (top_val != to_swap) {
           lock.unlock_shared();

           lock.lock();
           /* since the 'current' node might have changed or been deleted, we need to check it again' */
           if (start == NULL) {
               start = new Llist_node(to_swap);
               lock.unlock();
               return;
           }
           Llist_node *head = start;
           /* go to end */
           while (head->next != NULL) {
               head = head->next;
           }

           if (head == current) {
               /* Good! */
               current->data = to_swap;
           }
           lock.unlock();
       }
       else {
           lock.unlock_shared();
       }

    }

private:
    Llist_node *start;
    shared_mutex lock;
};
