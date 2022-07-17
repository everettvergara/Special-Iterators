# N-Deep Nested Loop (ndeep_loop)

A lightweight C++ Class to simulate an N-Deep nested loop. Use this if the depth of the nested loop is unknown or the depth may vary during run-time. Applications of which vary from AI classification object comparator, multi-dimensional array/ vector value comparators, coding challenges, and more.

https://github.com/everettvergara/N-Deep-Loop

If you need to perform combination of values using a sub-set of a single dimensional array/ vector, 
check out my other repository for Index-Combinator: 

https://github.com/everettvergara/Index-Combinator


```c++

    for (int a = 0; a < a_max; ++a) {               // Depth 0
        for (int b = 0; b < b_max; ++b) {           // Depth 1
            ...                                     // Depth 2 to n - 2
            
            do_something_before_each_loop();        // Also called in upper loops
            for (int X = 0; ? < X_max; ++X) {       // Depth n - 1

                // Your main code goes here
                // ...
                // ...
            }
            do_something_after_each_loop();         // Also called in lower loops

        } 
    }

```

The core iterator is written elegantly and efficiently.

```c++

    auto iterator() -> bool {
        if (ptr_[i_] != end_[i_]) i_ = l_;
        while (++ptr_[i_] == end_[i_])
            if (ptr_[i_] = data_[i_]->data(); --i_ >= data_.size()) return false;
        return true;
    }

```

How to use it:

```c++

auto main(const int argc, const char *argv[]) -> int {
    init_vector_values();

    ndeep_loop<int> looper(print_before, print_after);
    for (auto &v : vec) looper.add_vector(&v);

    while(looper.iterate()) {
        for (auto &i : looper.ixs()) std::cout << "[" << i << "]"; std::cout << " - ";
        for (auto &i : looper.ix_ptr()) std::cout << *i << " "; std::cout << "\n";
    }
}

```

Important Notes:
--
- Not thread safe!
- Calling ix_ptr() and/or value_ptr() before iterate() is UB.
- Adding modifying the source vector during iterate() results in UB.