#ifndef LEFTIST_HEAP_BINARYNODE_H
#define LEFTIST_HEAP_BINARYNODE_H

#include <assert.h>
#include <algorithm>

template <class T>
struct BinaryNode {

    T key;
    int distance;
    BinaryNode* leftChild;
    BinaryNode* rightChild;

    BinaryNode() : leftChild(nullptr), rightChild(nullptr), distance(0) {}
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
int getDistance(BinaryNode<T> *x) {
    if (x == nullptr)
        return 0;
    return x->distance;
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
    x->distance = 1 + std::min(getDistance(x->leftChild), getDistance(x->rightChild));
    x->leftChild = child;
}

template <class T>
void setRightChild(BinaryNode<T>* x, BinaryNode<T>* child) {
    assert(x != nullptr);
    x->rightChild = child;
}

#endif //LEFTIST_HEAP_BINARYNODE_H
