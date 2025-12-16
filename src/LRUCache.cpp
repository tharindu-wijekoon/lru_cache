// LRUCache.cpp
#include "LRUCache.h"

using namespace std;

LRUCache::LRUCache(size_t capacity) : capacity_(capacity) {}

int LRUCache::get(int key) {
    auto it = cache_map_.find(key);
    if (it == cache_map_.end()) {
        return -1;
    }

    // Move accessed item to front
    cache_list_.splice(cache_list_.begin(), cache_list_, it->second);
    return it->second->second;
}

void LRUCache::put(int key, int value) {
    auto it = cache_map_.find(key);

    if (it != cache_map_.end()) {
        it->second->second = value;
        cache_list_.splice(cache_list_.begin(), cache_list_, it->second);
        return;
    }

    if (cache_map_.size() == capacity_) {
        auto lru = cache_list_.back();
        cache_map_.erase(lru.first);
        cache_list_.pop_back();
    }

    cache_list_.emplace_front(key, value);
    cache_map_[key] = cache_list_.begin();
}