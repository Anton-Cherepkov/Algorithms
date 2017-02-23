#ifndef SPLAYTREE_SPLAYTREE_H
#define SPLAYTREE_SPLAYTREE_H

#include "BinaryNode.h"

#include <stdexcept>
#include <string>
#include <ostream>
#include <utility>

template <class T>
class SplayTree {

private:

    typedef BinaryNode<T> Node;

    Node* _root;
    size_t _size;

    void rotateRight(Node* x) {
        assert(x != nullptr);
        assert(getLeftChild(x) != nullptr);

        Node* y = getLeftChild(x);
        Node* alpha = getLeftChild(y);
        Node* betta = getRightChild(y);
        Node* gamma = getRightChild(x);

        if (x == _root)
            _root = y;
        else {
            if (isLeftChild(x))
                setLeftChild(parent(x), y);
            else
                setRightChild(parent(x), y);
        }

        setRightChild(y, x);
        setLeftChild(x, betta);
    }

    void rotateLeft(Node* x) {
        assert(x != nullptr);
        assert(getRightChild(x) != nullptr);

        Node* y = getRightChild(x);
        Node* alpha = getLeftChild(x);
        Node* betta = getLeftChild(y);
        Node* gamma = getRightChild(y);

        if (x == _root)
            _root = y;
        else {
            if (isLeftChild(x))
                setLeftChild(parent(x), y);
            else
                setRightChild(parent(x), y);
        }

        setLeftChild(y, x);
        setRightChild(x, betta);
    }

    void zig(Node* x) {
        assert(x != nullptr);
        assert(parent(x) == _root);

        if (isLeftChild(x))
            rotateRight(parent(x));
        else
            rotateLeft(parent(x));
    }

    void zig_zig(Node* x) {
        assert(x != nullptr);
        assert(parent(x) != nullptr && parent(parent(x)) != nullptr);
        assert(isLeftChild(x) && isLeftChild(parent(x)) || isRightChild(x) && isRightChild(parent(x)));

        if (isLeftChild(x) && isLeftChild(parent(x))) {
            rotateRight(parent(parent(x)));
            rotateRight(parent(x));
        } else {
            rotateLeft(parent(parent(x)));
            rotateLeft(parent(x));
        }
    }

    void zig_zag(Node* x) {
        assert(x != nullptr);
        assert(parent(x) != nullptr && parent(parent(x)) != nullptr);
        assert(isLeftChild(x) && isRightChild(parent(x)) || isRightChild(x) && isLeftChild(parent(x)));

        if (isLeftChild(x)) {
            rotateRight(parent(x));
            rotateLeft(parent(x));
        } else {
            rotateLeft(parent(x));
            rotateRight(parent(x));
        }
    }

    void splay(Node* x) {
        assert(x != nullptr);

        while (x != _root) {
            if (parent(x) == _root)
                zig(x);
            else if (isLeftChild(x) && isLeftChild(parent(x)) || isRightChild(x) && isRightChild(parent(x)))
                zig_zig(x);
            else
                zig_zag(x);
            splay(x);
        }
    }

    Node* find(T key) {
        if (_root == nullptr)
            return nullptr;

        Node* current = _root;
        for (;;) {

            if (getKey(current) == key) {
                splay(current);
                return current;
            }

            if (key < getKey(current)) {
                if (getLeftChild(current) == nullptr) {
                    splay(current);
                    return nullptr;
                }
                current = getLeftChild(current);
            } else {
                if (getRightChild(current) == nullptr) {
                    splay(current);
                    return nullptr;
                }
                current = getRightChild(current);
            }

        }
    }

    void clear(Node *x) {
        if (x == nullptr)
            return;
        clear(getLeftChild(x));
        clear(getRightChild(x));
        delete x;
    }

    void preOrderTraversal(Node* x, std::ostream& out) {
        if (x == nullptr)
            return;
        preOrderTraversal(getLeftChild(x), out);
        out << getKey(x) << ' ';
        preOrderTraversal(getRightChild(x), out);
    }

    void postOrderTraversal(Node* x, std::ostream& out) {
        if (x == nullptr)
            return;
        postOrderTraversal(getLeftChild(x), out);
        out << getKey(x) << ' ';
        postOrderTraversal(getRightChild(x), out);
    }

public:

    SplayTree() : _root(nullptr), _size(0) {}

    SplayTree& operator =(const SplayTree& other) = delete;

    void swap(SplayTree& other) {
        std::swap(_size, other._size);
        std::swap(_root, other._root);
    }

    ~SplayTree() {
        clear();
    }

    bool add(T key) {
        if (_root == nullptr) {
            _root = new Node(key);
            ++_size;
            return true;
        }

        Node* current = _root;
        Node* child;
        for (;;) {

            if (getKey(current) == key)
                return false;

            if (key < getKey(current)) {
                child = getLeftChild(current);
                if (child == nullptr) {
                    Node* newNode = new Node(key);
                    setLeftChild(current, newNode);
                    splay(newNode);
                    ++_size;
                    return true;
                }
            } else {
                child = getRightChild(current);
                if (child == nullptr) {
                    Node* newNode = new Node(key);
                    setRightChild(current, newNode);
                    splay(newNode);
                    ++_size;
                    return true;
                }
            }

            current = child;

        }
    }

    bool contains(T key) {
        return find(key) != nullptr;
    }

    bool remove(T key) {
        if (find(key) == nullptr)
            return false;

        --_size;

        Node* leftChild = getLeftChild(_root);
        Node* rightChild = getRightChild(_root);
        delete _root;

        if (leftChild == nullptr) {
            _root = rightChild;
            if (rightChild != nullptr)
                rightChild->parent = nullptr;
            return true;
        }
        leftChild->parent = nullptr;
        _root = leftChild;

        Node* current = leftChild;
        Node* next = getRightChild(current);
        while (next != nullptr) {
            current = next;
            next = getRightChild(current);
        }
        splay(current);
        setRightChild(current, rightChild);

        return true;
    }

    T minimum() {
        if (_root == nullptr) {
            throw std::out_of_range("Minimal element is not defined for an empty tree");
        }

        Node* current = _root;
        Node* next = getLeftChild(current);
        while (next != nullptr) {
            current = next;
            next = getLeftChild(current);
        }
        splay(current);

        return getKey(_root);
    }

    T maximum() {
        if (_root == nullptr) {
            throw std::out_of_range("Maximal element is not defined for an empty tree");
        }

        Node* current = _root;
        Node* next = getRightChild(current);
        while (next != nullptr) {
            current = next;
            next = getRightChild(current);
        }
        splay(current);

        return getKey(_root);
    }

    size_t size() const {
        return _size;
    }

    void clear() {
        clear(_root);
        _root = nullptr;
        _size = 0;
    }

    void printAscending(std::ostream& out = std::cout) {
        preOrderTraversal(_root, out);
    }

    void printDescending(std::ostream& out = std::cout) {
        postOrderTraversal(_root, out);
    }

};



#endif //SPLAYTREE_SPLAYTREE_H
