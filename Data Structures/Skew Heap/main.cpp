#include <iostream>

#include "SkewHeap.h"

int main() {

    SkewHeap<int> s;

    srand(time(0));
    for (int i = 0; i < 50; ++i) {
        s.insert(rand());
    }
    while (!s.empty()) {
        std::cout << s.extract_max() << ", Elements left: " << s.size() << '\n';
    }
    
    return 0;
}