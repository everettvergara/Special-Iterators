#include <iostream>
#include "combo_loop.hpp"

using namespace g80;

auto main(const int argc, const char *argv[]) -> int {

    std::vector<int> vec;
    for (size_t i = 1; i <= 10; ++i) vec.emplace_back(i);

    combo_loop<int> looper(3);
    looper.add_vector_ptr(&vec);

    // while(looper.iterate());
    // looper.clear();
    // for (auto &v : vec) looper.add_vector_ptr(&v);

    while(looper.iterate()) {
        for (auto &i : looper.ix()) std::cout << i << " " ;
        // for (auto &p : looper.ptr()) std::cout << *p << " " ;
        std::cout << "\n";
    }
    std::cout << std::endl;

}