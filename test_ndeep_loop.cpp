#include <iostream>
#include "ndeep_loop.hpp"

using namespace g80;

auto main(const int argc, const char *argv[]) -> int {

    std::vector<std::vector<int>> vec;
    for (size_t i = 0; i != 3; ++i) vec.emplace_back(std::vector<int>());
    for (size_t a = 1; a != 5; ++a) vec[0].emplace_back(a);
    for (size_t b = 11; b != 15; ++b) vec[1].emplace_back(b);
    for (size_t c = 101; c != 105; ++c) vec[2].emplace_back(c);


    ndeep_loop<int> looper;
    for (auto &v : vec) looper.add_vector_ptr(&v);

    // while(looper.iterate()) {

    // }

}