## Build & Run

```bash
if (!(Test-Path build)) { mkdir build }
g++ -std=c++17 -O2 ./src/LRUCache.cpp ./test/initial.cpp -o ./build/initial_test
./build/initial_test
```
note: you can run different tests in the ./test directory.