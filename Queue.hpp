#include <cstdlib>
#include "SLNode.hpp"
#ifndef QUEUE
#define QUEUE
template <typename T>
class Queue{
private:
    SLNode<T>* first;
    SLNode<T>* last;
    size_t count;
public:
    
    Queue(){
        first = last = nullptr;
        count = 0;
    }

    ~Queue(){
        while(first) {
            pop();
        }
    }
    void push(T data) {
        if (!count) {
            last = new SLNode<T>(data);
            first = last;
        }
        else {
          last->next = new SLNode<T>(data);
          last = last->next;
        }
        count++;

    }
    void pop() {
        if (count) {
            SLNode<T>* toDelete = first;
            first = first->next;
            delete toDelete;
            if (!first) {
                last = nullptr;
            }
            count--;
        }
        
    }
    T front() {
        return(count)? first->data : NULL ;
    }
    T back() {
        return(count)? last->data : NULL;
    }
    size_t size() {
        size_t count = 0;
        SLNode<T>* runner = first;
        while(runner) {
            runner = runner->next;
            count++;
        }
        return count;
    }


};
#endif