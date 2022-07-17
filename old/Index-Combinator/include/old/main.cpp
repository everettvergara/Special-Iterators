#include <iostream>
#include <string>

#include "IndexCombinator.h"

using namespace g80;

auto debug(const StackIxs &ixs) -> void;

auto main(int argc, char **argv) -> int {
    std::string unique {"abcde"}; 

    IndexCombinator combo_ix(unique.size(), 3);
    const StackIxs &ixs = combo_ix.get();

    int ctr = 0;
    do {
        std::cout << ++ctr << ". ";
        for (int i = 0; i < combo_ix.R(); ++i)
            std::cout << " " << unique[ixs[i]];
        std::cout << "\n";
    } while(combo_ix.next());
}

auto debug(const StackIxs &ixs) -> void {
    for (Integer i = 0; i < ixs.size(); ++i)
        std::cout << ixs[i] << " ";
    std::cout << "\n";
}