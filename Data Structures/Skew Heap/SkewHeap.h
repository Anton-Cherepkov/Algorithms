#ifndef SKEW_HEAP_SKEWHEAP_H
#define SKEW_HEAP_SKEWHEAP_H

#include "BinaryNode.h"

#include <functional>

template <class T>
class SkewHeap {

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

    SkewHeap() : _root(nullptr), _size(0) {}
    SkewHeap& operator =(const SkewHeap& other) = delete;
    ~SkewHeap() {
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

#endif //SKEW_HEAP_SKEWHEAP_H