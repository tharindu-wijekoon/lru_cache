// LRUCache.cpp
#include "LRUCache.h"

template<typename K, typename V, typename Hash>
LRUCache<K, V, Hash>::LRUCache(size_t capacity, std::chrono::seconds ttl) 
    : capacity_(capacity), ttl_(ttl) {}

template<typename K, typename V, typename Hash>
bool LRUCache<K, V, Hash>::is_expired(const Entry& entry) const {
    if (ttl_.count() == 0) return false;
    return std::chrono::steady_clock::now() >= entry.expires_at;
}

template<typename K, typename V, typename Hash>
bool LRUCache<K, V, Hash>::get(const K& key, V& value) {
    auto it = cache_map_.find(key);
    if (it == cache_map_.end())
        return false;

    if (is_expired(*(it->second))) {
        cache_list_.erase(it->second);
        cache_map_.erase(it);
        return false;
    }

    // Move accessed item to front
    cache_list_.splice(cache_list_.begin(), cache_list_, it->second);
    value = it->second->value;
    return true;
}

template<typename K, typename V, typename Hash>
void LRUCache<K, V, Hash>::put(const K& key, const V& value) {
    auto now = std::chrono::steady_clock::now();
    auto expires_at = ttl_.count() == 0
        ? std::chrono::steady_clock::time_point::max()
        : now + ttl_;

    auto it = cache_map_.find(key);

    if (it != cache_map_.end()) {
        it->second->value = value;
        it->second->expires_at = expires_at;
        cache_list_.splice(cache_list_.begin(), cache_list_, it->second);
        return;
    }

    if (cache_list_.size() == capacity_) {
        auto lru = cache_list_.back();
        cache_map_.erase(lru.key);
        cache_list_.pop_back();
    }

    cache_list_.push_front({key, value, expires_at});
    cache_map_[key] = cache_list_.begin();
}