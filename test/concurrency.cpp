#include "../src/ThreadSafeLRUCache.h"
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <sstream>

std::mutex cout_mutex;

void log(const std::string& message) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << message << std::endl;
}

int main() {
    ThreadSafeLRUCache cache(50);
    std::vector<std::thread> threads;

    log("Starting concurrent access test...");

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&cache, i]() {
            std::ostringstream oss;
            oss << "Thread " << i << " started.";
            log(oss.str());

            for (int j = 0; j < 1000; ++j) {
                int key = i * 1000 + j;

                cache.put(key, j);

                if (j % 200 == 0) {
                    std::ostringstream oss;
                    oss << "[Thread " << i << "] put key=" << key;
                    log(oss.str());
                }
                
                int value = cache.get(j);

                if (j % 200 == 0) {
                    std::ostringstream oss;
                    oss << "[Thread " << i << "] get key=" << j
                        << " -> " << value;
                    log(oss.str());
                }
            }

            std::ostringstream oss2;
            oss2 << "[Thread " << i << "] finished";
            log(oss2.str());
        });
    }

    for (auto& t : threads) t.join();

    log("Concurrent access test completed.");
    return 0;
}