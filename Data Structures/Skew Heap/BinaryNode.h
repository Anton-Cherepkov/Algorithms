#ifndef SKEW_HEAP_BINARYNODE_H
#define SKEW_HEAP_BINARYNODE_H

#include <assert.h>

template <class T>
struct BinaryNode {

    T key;
    BinaryNode* leftChild;
    BinaryNode* rightChild;

    BinaryNode() : leftChild(nullptr), rightChild(nullptr) {}
    BinaryNode(T key) : BinaryNode() {
        this-> key = key;
    }
    ~BinaryNode() {}

};

template <class T>
T& getKey(BinaryNode<T> *x) {
    assert(x != nullptr);
    return x->key;
}

template <class T>
BinaryNode<T>* getLeftChild(BinaryNode<T> *x) {
    assert(x != nullptr);
    return x->leftChild;
}

template <class T>
BinaryNode<T>* getRightChild(BinaryNode<T> *x) {
    assert(x != nullptr);
    return x->rightChild;
}

template <class T>
void setLeftChild(BinaryNode<T>* x, BinaryNode<T>* child) {
    assert(x != nullptr);
    x->leftChild = child;
}

template <class T>
void setRightChild(BinaryNode<T>* x, BinaryNode<T>* child) {
    assert(x != nullptr);
    x->rightChild = child;
}

#endif //SKEW_HEAP_BINARYNODE_H
