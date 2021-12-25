#include <iostream>
#include <vector>
#include "unordered_map.h"

int main() {
    unordered_map<int, int, std::hash<int>, std::equal_to<>> um1;
    return 0;
}
