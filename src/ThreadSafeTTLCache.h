// ThreadSafeTTLCache.h
#pragma once
#include "LRUCache.h"
#include <shared_mutex>
#include <condition_variable>
#include <thread>

template<typename K, typename V, typename Hash = std::hash<K>>
class ThreadSafeTTLCache {
public:
    explicit ThreadSafeTTLCache(
        size_t capacity,
        std::chrono::seconds ttl,
        std::chrono::seconds cleanup_interval
    );

    ~ThreadSafeTTLCache();

    bool get(const K& key, V& value);
    void put(const K& key, const V& value);

private:
    void cleanup_loop(std::stop_token stoken);

    LRUCache<K, V, Hash> cache_;
    mutable std::shared_mutex mutex_;

    std::jthread cleaner_;
    std::chrono::seconds cleanup_interval_;
};