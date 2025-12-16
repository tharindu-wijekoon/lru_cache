// ThreadSafeLRUCache.cpp
#include "ThreadSafeLRUCache.h"

template<typename K, typename V, typename Hash>
ThreadSafeLRUCache<K, V, Hash>::ThreadSafeLRUCache(size_t capacity, std::chrono::seconds ttl) : cache_(capacity, ttl) {}

template<typename K, typename V, typename Hash>
bool ThreadSafeLRUCache<K, V, Hash>::get(const K& key, V& value) {
    // LRU get() mutates internal state → must be exclusive
    std::unique_lock<std::shared_mutex> lock(mutex_);
    return cache_.get(key, value);
}

template<typename K, typename V, typename Hash>
void ThreadSafeLRUCache<K, V, Hash>::put(const K& key, const V& value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    return cache_.put(key, value);
}
