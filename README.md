# Special-Iterators
A collection of special iterators like combinators and permutators in C/C++.

N-Deep Nested Loops
---
A lightweight C++ Class to simulate an N-Deep Nested Loop. Use this if the depth of the nested loop is unknown or the depth may vary during run-time. Applications of which vary from AI classification object comparator, multi-dimensional array/ vector value comparators, coding challenges, and more.

In a N-Deep Nested Loop, what we are trying to achieve is like:

```c++

    // Assuming you want to 
    // match indexes A (0) to Z (n - 1)
    for (int a = 0; a < a_max; ++a) {           // Depth 0
        for (int b = 0; b < b_max; ++b) {       // Depth 1
            ...                                 // Depth 2 to n - 2
            for (int z = 0; ? < z_max; ++z) {   // Depth n - 1
                // Your main code goes here
            }
        } 
    }
```

How to use it:

```c++
#include <iostream>
#include "ndeep_loop.hpp"

using namespace g80;

auto main(const int argc, const char *argv[]) -> int {

    // You have a vector of vector<T>
    std::vector<std::vector<int>> vec;
    for (size_t i = 0; i != 3; ++i) vec.emplace_back(std::vector<int>());
    for (size_t a = 1; a <= 5; ++a) vec[0].emplace_back(a);
    for (size_t b = 11; b <= 15; ++b) vec[1].emplace_back(b);
    for (size_t c = 101; c <= 105; ++c) vec[2].emplace_back(c);

    // Declare a looper<T>
    ndeep_loop<int> looper;

    // Add a pointer to your vector<T>
    for (auto &v : vec) looper.add_vector_ptr(&v);

    // Iterate
    while(looper.iterate()) {

        // Use the indexes
        for (auto &i : looper.ix()) std::cout << i << " " ;

        // Or access the values directly
        for (auto &p : looper.ptr()) std::cout << *p << " " ;
        std::cout << "\n";
    }
    std::cout << std::endl;
}
```

What ix() and ptr() represents?
```c++
    Z[?]                        = {, , , , ...}
                                        ^
    B[?]            = {, , , , ...}     |
                           ^            |
    A[?] = {, , , , ...}   |            |
             ^             |            |
             |             |            |
    ix[0]  --+             |            |
    ix[1]  ----------------+            |
    ix[25] -----------------------------+

    Indexes = index
    Pointers = address

```