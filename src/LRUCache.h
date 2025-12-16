// LRUCache.h
#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <cstddef>
#include <unordered_map>
#include <list>
#include <utility>

class LRUCache {
public:
    explicit LRUCache(size_t capacity);

    int get(int key);
    void put(int key, int value);

private:
    size_t capacity_;
    std::list<std::pair<int, int>> cache_list_;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache_map_;
};

#endif // LRU_CACHE_H