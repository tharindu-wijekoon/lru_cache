// ThreadSafeTTLCache.cpp
#include "ThreadSafeTTLCache.h"

template<typename K, typename V, typename Hash>
ThreadSafeTTLCache<K, V, Hash>::ThreadSafeTTLCache(
    size_t capacity,
    std::chrono::seconds ttl,
    std::chrono::seconds cleanup_interval)
    : cache_(capacity, ttl),
      cleanup_interval_(cleanup_interval),
      cleaner_([this](std::stop_token st) { cleanup_loop(st); }) {}

template<typename K, typename V, typename Hash>
void ThreadSafeTTLCache<K, V, Hash>::cleanup_loop(std::stop_token stoken) {
    while (!stoken.stop_requested()) {
        std::this_thread::sleep_for(cleanup_interval_);

        std::unique_lock<std::shared_mutex> lock(mutex_);

        // brute-force cleanup (simple + safe)
        for (auto it = cache_.cache_list_.begin();
            it != cache_.cache_list_.end();) {
            if (cache_.is_expired(*it)) {
                cache_.cache_map_.erase(it->key);
                it = cache_.cache_list_.erase(it);
            } else {
                ++it;
            }
        }
    }
}

template<typename K, typename V, typename Hash>
bool ThreadSafeTTLCache<K, V, Hash>::get(const K& key, V& value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    return cache_.get(key, value);
}

template<typename K, typename V, typename Hash>
void ThreadSafeTTLCache<K, V, Hash>::put(const K& key, const V& value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    cache_.put(key, value);
}