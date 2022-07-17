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