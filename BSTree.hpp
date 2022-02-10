#include <cstdlib>
#include "DLNode.hpp"
#include "Queue.hpp"
#include <queue>
using namespace std;
enum Traversal {Prefix, Infix, PostFix, Decroissant, BreathFirst};
template <typename T>

class BSTree {
private:
    DLNode<T>* root;
    size_t count;

    void prefixTraversal(DLNode<T>* node, Queue<T>* traversalQueue) {
        traversalQueue->push(node->data);
        if (node->left) {
            prefixTraversal(node->left, traversalQueue);
        }
        if (node->right) {
            prefixTraversal(node->right, traversalQueue);
        }
    }
    void infixTraversal(DLNode<T>* node, Queue<T>* traversalQueue) {
        if (node->left) {
            infixTraversal(node->left, traversalQueue);
        }
        traversalQueue->push(node->data);
        if (node->right) {
            infixTraversal(node->right, traversalQueue);
        }
    }
    
    void postfixTraversal(DLNode<T>* node, Queue<T>* traversalQueue) {
        if (node->left) {
            postfixTraversal(node->left, traversalQueue);
        }
        if (node->right) {
            postfixTraversal(node->right, traversalQueue);
        }
        traversalQueue->push(node->data);
    }
    void decroissantTraversal(DLNode<T>* node, Queue<T>* traversalQueue) {
        if (node->right) {
            decroissantTraversal(node->right, traversalQueue);
        }
        traversalQueue->push(node->data);
        if (node->left) {
            decroissantTraversal(node->left, traversalQueue);
        }
    }
    void breathFirst(Queue<T>* traversal, Queue<DLNode<T>*>* queue) {
        while (queue->size()) {
            if (queue->front()->left) {
                queue->push(queue->front()->left);
            } 
            if (queue->front()->right) {
                queue->push(queue->front()->right);
            } 
            traversal->push(queue->front()->data);
            queue->pop();
        }
    }
   
public:
    BSTree() {
        root = nullptr;
        count = 0;
    }
    void add(T data) {
        if (root) {
            DLNode<T>* runner = root;
            while(runner) {
                if (data < runner->data) {
                    if (runner->left) {
                        runner = runner->left;
                    }
                    else {
                        runner->left = new DLNode<T>(data);
                        runner = nullptr;
                        count++;
                    }
                }
                else if (data > runner->data){
                    if (runner->right) {
                        runner = runner->right;
                    }
                    else {
                        runner->right = new DLNode<T>(data);
                        runner = nullptr;
                        count++;
                    }
                } 
                else {
                    runner = nullptr;
                }
            } 
        }
        else {
            root = new DLNode<T>(data);
            root->data = data;
            count++;
        }
    }
    bool search(T data) {
        if (root) {
            DLNode<T>* runner = root;
            while(runner) {
                if (data < runner->data) {
                    runner = runner->left;
                }
                else if (data > runner->data){
                    runner = runner->right;
                } 
                else {
                    return true;
                }
            } 
            return false;
        }
        return false;
    }
    Queue<T>* Traversal(Traversal type) {
        Queue<T>* traversalQueue = new Queue<T>();
        if (root) {
            switch (type) {
                case Traversal::Prefix:
                    prefixTraversal(root, traversalQueue);
                    break;
                    
                case Traversal::Infix:
                    infixTraversal(root, traversalQueue);
                    break;

                case Traversal::PostFix:  
                    postfixTraversal(root, traversalQueue);
                    break;

                case Traversal::Decroissant:
                    decroissantTraversal(root, traversalQueue);
                    break;

                case Traversal::BreathFirst:
                    Queue<DLNode<T>*>* tmpQueue = new Queue<DLNode<T>*>();
                    tmpQueue->push(root);
                    breathFirst(traversalQueue, tmpQueue);
                    delete tmpQueue;
                    
            }
        }
        return traversalQueue;
    }
    void remove(T data) {
        if (root) {
    
            DLNode<T>* parent = root;
            DLNode<T>* toDelete = nullptr;
            while(toDelete == nullptr) {
                if (data < parent->data) {
                    if (!parent->left) {
                        return;
                    }
                    else if (parent->left->data == data) {
                        toDelete = parent->left;
                        
                    }
                    else {
                        parent = parent->left;
                    }
                    
                }
                
                else if(data > parent->data) {
                    if (!parent->right) {
                        return;
                    }
                    else if(parent->right->data == data) {
                        toDelete = parent->right;
                        
                    }
                    else {
                        parent = parent->right;
                    }
                }
                else {
                    toDelete = parent;
                }

            } 
                        
            if (!toDelete->left && !toDelete->right ) {
                if (parent->left == toDelete) {
                    parent->left = nullptr;
                }
                else if(parent->right == toDelete){
                    parent->right = nullptr;
                }
                delete toDelete;
                if(toDelete == root) {
                    root = nullptr;
                    parent = nullptr;
                }
                            
            }
            else if (toDelete->left && toDelete->right) {
                DLNode<T>* runner = toDelete;
                runner = runner->right;
                while(runner->left) {
                    runner = runner->left;
                }
                T donnee = runner->data;
                remove(donnee);
                toDelete->data = donnee;
                count++;
            }
            
            else if (!toDelete->left && toDelete->right) {
                if (root == toDelete) {
                    root = toDelete->right;
                }
                else if (parent->left == toDelete) {
                    parent->left = toDelete->right;
                    delete toDelete;
                }
                else {
                    parent->right = toDelete->right;
                    delete toDelete;
                }
            }
            else {
                if (root == toDelete) {
                    root = toDelete->left;
                }
                else if (parent->left == toDelete) {
                    parent->left = toDelete->left;
                    delete toDelete;
                }
                else {
                    parent->right = toDelete->left;
                    delete toDelete;
                }
            }
            count--;
        }
                 
    }
    void clear() {
        while(count) {
            remove(root->data);
        }
        root = nullptr;
    }
    T first() {
        return root->data;
    }
    size_t size() {
        return count;
    }
};