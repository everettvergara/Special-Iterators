#include <iostream>
#include "combo_loop.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    // You have a vector
    std::vector<int> vec;
    for (size_t i = 1; i <= 10; ++i) vec.emplace_back(i);

    // Declare a combination looper and 
    // its subset to combinate
    combo_loop<int> looper(3);

    // Add your vector to the looper
    looper.add_vector_ptr(&vec);

    // Iterate
    while(looper.iterate()) {
        for (auto &i : looper.ix()) std::cout << i << " " ;
        for (auto &p : looper.ptr()) std::cout << *p << " " ;
        std::cout << "\n";
    }
    std::cout << std::endl;
}