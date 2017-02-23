#ifndef SPLAYTREE_BINARYNODE_H
#define SPLAYTREE_BINARYNODE_H

#include <assert.h>

template <class T>
struct BinaryNode {

    T key;
    BinaryNode* leftChild;
    BinaryNode* rightChild;
    BinaryNode* parent;

    BinaryNode() : leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}
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
    if (child != nullptr)
        child->parent = x;
}

template <class T>
void setRightChild(BinaryNode<T>* x, BinaryNode<T>* child) {
    assert(x != nullptr);
    x->rightChild = child;
    if (child != nullptr)
        child->parent = x;
}

template <class T>
BinaryNode<T>* parent(BinaryNode<T>* x) {
    assert(x != nullptr);
    return x->parent;
}

template <class T>
bool isLeftChild(BinaryNode<T>* x) {
    assert(x != nullptr);
    assert(parent(x) != nullptr);
    return x == getLeftChild(parent(x)) ? true : false;
}

template <class T>
bool isRightChild(BinaryNode<T>* x) {
    return !isLeftChild(x);
}

#endif //SPLAYTREE_BINARYNODE_H
