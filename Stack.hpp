#include <cstdlib>
#include <type_traits>
#include "SLNode.hpp"
template <typename T> 

class Stack {
private:
    SLNode<T>* first;
    size_t count;
public:
    Stack() {
        this->first = nullptr;
        count = 0;
    }
    ~Stack() {
        while(first) {
            pop();
        }
    }
    void push(T data) {
        first = new SLNode<T>(data, first); 
        count++;
    }
    void pop() {
        if (count) {
            SLNode<T>* toDelete = first;
            first = first->next;
            delete toDelete;
            count--;
        }
    }
    T top() {
        return (count) ? first->data : NULL;
    }
    size_t size() {
        return count;
    }
};