#ifndef LEFTIST_HEAP_LEFTISTHEAP_H
#define LEFTIST_HEAP_LEFTISTHEAP_H

#include "BinaryNode.h"

#include <functional>

template <class T>
class LeftistHeap {

private:

    typedef BinaryNode<T> Node;

    Node* _root;
    size_t _size;

    Node* merge(Node* x, Node* y) const {
        if (x == nullptr || y == nullptr)
            return x == nullptr ? y : x;
        if (getKey(x) >= getKey(y))
            std::swap(x, y);

        setRightChild(x, merge(getRightChild(x), y));
        if (getDistance(getRightChild(x)) > getDistance(getLeftChild(x)))
            std::swap(x->leftChild, x->rightChild);

        return x;
    }

    void clear(Node *x) {
        if (x == nullptr)
            return;
        clear(getLeftChild(x));
        clear(getRightChild(x));
        delete x;
    }


public:

    LeftistHeap() : _root(nullptr), _size(0) {}
    LeftistHeap& operator =(const LeftistHeap& other) = delete;
    ~LeftistHeap() {
        _root = nullptr;
        clear();
    }

    void insert(T val) {
        ++_size;
        _root = merge(_root, new Node(val));
    }

    T min() const {
        return getKey(_root);
    }

    T extract_max() {
        --_size;
        T temp = min();
        Node* leftChildOfRoot = getLeftChild(_root);
        Node* rightChildOfRoot = getRightChild(_root);
        delete _root;
        _root = merge(leftChildOfRoot, rightChildOfRoot);
        return temp;
    }

    void clear() {
        clear(_root);
        _root = nullptr;
        _size = 0;
    }

    size_t size() const {
        return _size;
    }

    bool empty() const {
        return !_size;
    }

};

#endif //LEFTIST_HEAP_LEFTISTHEAP_H