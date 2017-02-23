#include <iostream>

#include "SplayTree.h"

int main() {
    SplayTree<int> tree;
    tree.add(1);
    tree.add(2);
    std::cout << tree.add(2) << '\n';
    std::cout << tree.remove(2) << '\n';
    std::cout << tree.remove(2) << '\n';
    tree.clear();
    std::cout << tree.size();
}