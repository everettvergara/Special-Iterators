# Special-Iterators
A collection of special iterators to mix-match, combinate, or permutate vectors in C/C++. 

    itr
    |
    +---+--> ndeep_loop
        |
        +--> combo_loop 

The base class of itr has the following declarations:

```c++
#pragma once
#include <vector>
#include <functional>

namespace g80 {
    template<typename T> class itr {

    protected:

        // Indexes that points to the data to iterate
        std::vector<size_t> ix_;

        // Points to the values of the indexes to iterate
        std::vector<T *> ix_ptr_;

        // The function called when iterate() is called
        std::function<auto () -> bool> f_;

        // A function to always return false
        auto invalid() -> bool {return false;}

        // A virtual function to be called on next iteration
        virtual auto next() -> bool {return false;}

        // A virtual function to be called on the first iterate
        virtual auto init() -> bool {return false;}    
    
    public:

        itr(const std::function<auto () -> bool> &f) : f_(f) {}
        auto iterate() -> bool {return f_();}

        // A virtual function to reset. 
        // Reset means reset the values but no the allocation
        virtual auto reset() -> void {}

        // Clear means remove the allocations
        virtual auto clear() -> void {}

        // Add pointer to the data to iterate
        virtual auto add_vector_ptr(std::vector<T> *v) -> void {}

        // A reference to ix_;
        virtual inline auto ix() const -> const std::vector<size_t> & {return ix_;}

        // A reference to ix_ptr;
        virtual inline auto ptr() -> const std::vector<T *> & {return ix_ptr_;}        
    };
}
```

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

Combo Loop
---
A lightweight C++ Class to iterate the combinations of a vector for subset r. If the size of the vector is n the size of the subset is r then the number of combinations to iterate is: nCr = n! / r!(n - r)!, where ! denotes factorial.

How to use it:
```c++
#include <iostream>
#include "combo_loop.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    // You have a vector<T>
    std::vector<int> vec;
    for (size_t i = 1; i <= 10; ++i) vec.emplace_back(i);

    // Declare a combo_loop<T> and 
    // its subset (i.e, 3) to combinate
    combo_loop<int> looper(3);

    // Add a pointer to your vector<T>
    looper.add_vector_ptr(&vec);

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

    A[?] = {, , , , , , , , , , , , , , , , , ...}
             ^             ^            ^
             |             |            |
    ix[0]  --+             |            |
    ix[1]  ----------------+            |
    ix[2]  -----------------------------+

    Indexes = index
    Pointers = address
```