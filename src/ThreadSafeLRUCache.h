// ThreadSafeLRUCache.h
#pragma once
#include "LRUCache.h"
#include <mutex>
#include <shared_mutex>

template<typename K, typename V, typename Hash = std::hash<K>>
class ThreadSafeLRUCache {
public:
    explicit ThreadSafeLRUCache(
        size_t capacity,
        std::chrono::seconds ttl = std::chrono::seconds(0)
    );

    bool get(const K& key, V& value);
    void put(const K& key, const V& value);

private:
    LRUCache<K, V, Hash> cache_;
    mutable std::shared_mutex mutex_;
};