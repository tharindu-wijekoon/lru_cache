#include "../src/LRUCache.h"
#include <iostream>

int main() {
    LRUCache cache(2); // capacity 2

    cache.put(1, 1);
    cache.put(2, 2);
    std::cout<< cache.get(1) << std::endl;

    cache.put(3, 30); // evicts key 2
    std::cout<< cache.get(2) << std::endl; // returns -1 (not found)

    cache.put(4, 40); // evicts key 1
    std::cout << cache.get(1) << std::endl; // -1
    std::cout << cache.get(3) << std::endl; // 30
    std::cout << cache.get(4) << std::endl; // 40

    int i;
    std::cin >> i;
}