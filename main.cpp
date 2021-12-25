#include <iostream>
#include <vector>
#include "unordered_map.h"

int main() {
    list<int> l1;
    for (size_t i = 0; i < 10; ++i) {
        l1.add(i);
    }
    auto it = l1.begin() + 3;
    it = l1.erase(it);
    std::cout << *it << std::endl;
    l1.print();
    return 0;
}
