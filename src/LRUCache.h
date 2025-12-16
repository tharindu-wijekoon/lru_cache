// LRUCache.h
#include <unordered_map>
#include <list>
#include <chrono>

template<
    typename K,
    typename V,
    typename Hash = std::hash<K>
>
class LRUCache {
public:
    explicit LRUCache(
        size_t capacity,
        std::chrono::seconds ttl = std::chrono::seconds(0)
    );

    bool get(const K& key, V& value);
    void put(const K& key, const V& value);

private:
    struct Entry {
        K key;
        V value;
        std::chrono::steady_clock::time_point expires_at;
    };

    size_t capacity_;
    std::chrono::seconds ttl_;

    std::list<Entry> cache_list_;
    std::unordered_map<K, std::list<Entry>::iterator, Hash> cache_map_;

    bool is_expired(const Entry& entry) const;
};