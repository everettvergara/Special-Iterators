# IndexCombinator

Recently, our Computer Vision Project required us to check the safe distance between detected objects in CCTV footages. The solution we've implemented uses Priority Queues and Combinations. Since there's no readily available Index Combinator in C++ I've written a class and generalize it for future use. 

For anyone working with Combinations (not to be confused with Permutations), here's the link to my IndexCombinator Class in C++. Please modify at will.

https://github.com/everettvergara/IndexCombinator

IMPORTANT: This assumes the objects represented for by the indexes are unique.

I've written it using stacks represented by int_type[] to minimize the push/pop (vs. std::stacks) and to eliminate stack frames (vs. recursion).

Combination:
---
Combination is the number of ways a subset of a set can be arranged regardless of its elements' position.

The formula for Combinations: C(n, r) = n! / (r! x (n - r)!)
Where:

    C = Combination Function
    n = Size of the set
    r = Size of the subset

Given the Set {0, 1, 2, 3, 4} where n = 5 and r = 3, the number of combinations = 10

```
What we're trying to do is generate all the index combinations of size R for the given N

1.	0, 1, 2
2.	0, 1, 3, we can't match 0 with arrangement 2, 1 because it is the same as above. 
                It violates the definition of Combination.
3.	0, 1, 4
4.	0, 2, 3
5.	0, 2, 4
6.	0, 3, 4
7.	1, 2, 3
8.	1, 2, 4
9.	1, 3, 4
10.	2, 3, 4

```

How to use it
---
```c++
#include <iostream>
#include "index_combinator.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {

    index_combinator<int> ic(5, 3);
    do {
        for (auto &r : ic) std::cout << r << " "; std::cout << "\n";
    } while (ic.next());
}

```


Output
---
```c++

0 1 2 
0 1 3 
0 1 4 
0 2 3 
0 2 4 
0 3 4 
1 2 3 
1 2 4 
1 3 4 
2 3 4 

```

Issue
---
Next update will primarily use pointers instead of index. Index will still be retained.
