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
        std::unique_lock excl(lock);

        if (start == NULL) {
            return -1;
        }

        if (start->next == NULL) {
            int ret = start->data;
            delete start;
            start = NULL;
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
        return ret;
    }


    int peek() {
        std::shared_lock shared(lock);

        if (start == NULL) {
            return -1;
        }

        Llist_node *current = start;
        while (current->next != NULL) {
            current = current->next;
        }
        return current->data;
    }

    void push(int p) {
        std::unique_lock excl(lock);

        if (start == NULL) {

            start = new Llist_node(p);
            return;
        }

        Llist_node *current = start;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new Llist_node(p);
    }

private:
    Llist_node *start;
    shared_mutex lock;
};

