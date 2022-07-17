# Special-Iterators
A collection of special iterators like combinators and permutators in C/C++.

N-Deep Nested Loops
---
A lightweight C++ Class to simulate an N-Deep Nested Loop. Use this if the depth of the nested loop is unknown or the depth may vary during run-time. Applications of which vary from AI classification object comparator, multi-dimensional array/ vector value comparators, coding challenges, and more.

In a N-Deep Nested Loop, what we are trying to achieve is like:

```c++
    for (int a = 0; a < a_max; ++a) {           // Depth 0
        for (int b = 0; b < b_max; ++b) {       // Depth 1
            ...                                 // Depth 2 to n - 2
            for (int z = 0; ? < z_max; ++z) {   // Depth (z) n - 1
                // Your main code goes here
                // ...
                // ...
            }
        } 
    }
```