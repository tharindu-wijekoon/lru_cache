// ThreadSafeLRUCache.cpp
#include "ThreadSafeLRUCache.h"

ThreadSafeLRUCache::ThreadSafeLRUCache(size_t capacity) : cache_(capacity) {}

int ThreadSafeLRUCache::get(int key) {
    // LRU get() mutates internal state → must be exclusive
    std::unique_lock<std::shared_mutex> lock(mutex_);
    return cache_.get(key);
}

void ThreadSafeLRUCache::put(int key, int value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    cache_.put(key, value);
}
