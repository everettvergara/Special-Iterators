#include <iostream>
#include <vector>
#include "ndeeploop.hpp"

using namespace g80;

std::vector<std::vector<int>> vec;
std::vector<std::vector<int> *> to_iterate;

auto init_vector_values() -> void;
auto print_before(const loop_struct<int> &ls) -> void;
auto print_after(const loop_struct<int> &ls) -> void;

auto main(const int argc, const char *argv[]) -> int {
    init_vector_values();
    
    ndeep_loop<int> looper(print_before, print_after);
    for (auto &v : vec) looper.add_vector(&v);

    while(looper.iterate()) {
        for (auto &i : looper.ixs()) std::cout << "[" << i << "]"; std::cout << " - ";
        for (auto &i : looper.ix_ptr()) std::cout << *i << " "; std::cout << "\n";
    }
}

auto init_vector_values() -> void {
    vec.emplace_back(std::vector<int>());
    vec.emplace_back(std::vector<int>());
    vec.emplace_back(std::vector<int>());

    // Initialize values
    for (size_t a = 1; a <= 5; ++a) vec[0].emplace_back(a);
    for (size_t b = 11; b <= 15; ++b) vec[1].emplace_back(b);
    for (size_t c = 101; c <= 105; ++c) vec[2].emplace_back(c);
}

auto print_before(const loop_struct<int> &ls) -> void {
    // std::cout << "bef: " << ls.depth() << std::string((ls.depth() + 1) * 3, '-') << " | " << "\n";
}

auto print_after(const loop_struct<int> &ls) -> void {
    // std::cout << "aft: " << ls.depth() << std::string((ls.depth() + 1) * 3, '-') << "\n";
}
