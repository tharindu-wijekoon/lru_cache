// ThreadSafeLRUCache.h
#pragma once
#include "LRUCache.h"
#include <mutex>
#include <shared_mutex>

class ThreadSafeLRUCache {
public:
    explicit ThreadSafeLRUCache(size_t capacity);

    int get(int key);
    void put(int key, int value);

private:
    LRUCache cache_;
    mutable std::shared_mutex mutex_;
};