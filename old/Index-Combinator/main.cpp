#include <iostream>
#include "index_combinator.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    index_combinator<int> ic(5, 3);
    do {
        for (auto &r : ic) std::cout << r << " "; std::cout << "\n";
    } while (ic.next());
}
