#ifndef SLNODE_HPP
#define SLNODE_HPP
template <typename T>
class SLNode {
public:
    T data;
    SLNode<T>* next; 
    SLNode(T data, SLNode<T>* next = nullptr){
        this->data = data;
        this->next = next;
    }

    ~SLNode(){

    }
};
#endif
