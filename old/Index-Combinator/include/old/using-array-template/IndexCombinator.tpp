#include "IndexCombinator.h"

template<g80::Integer N, g80::Integer R>
g80::IndexCombinator<N, R>::IndexCombinator() {
    reset();
}

template<g80::Integer N, g80::Integer R>
auto g80::IndexCombinator<N, R>::reset() -> void {
    stack_ptr_ = {R - 1};
    for (int i = 0; i < R; ++i) 
        stack_ixs_[i] = i;
}

template<g80::Integer N, g80::Integer R>
auto g80::IndexCombinator<N, R>::get() const -> const ArrayIx<R> & {
    return stack_ixs_;
}

template<g80::Integer N, g80::Integer R>
auto g80::IndexCombinator<N, R>::next() -> bool {
    // Early exit if end is reached
    if (stack_ptr_ < 0) 
        return false;

    // Pop the stack 
    while (stack_ixs_[stack_ptr_] == max(stack_ptr_))
        if (--stack_ptr_ < 0)
            return false;

    // Push to stack
    if (stack_ptr_ < R - 1) {
        int last = ++stack_ixs_[stack_ptr_];
        while (stack_ptr_ < R - 1)
            stack_ixs_[++stack_ptr_] = ++last;
    
    // Increment the last element of stack_ixs_
    } else
        ++stack_ixs_[stack_ptr_];

    return true;
}

template<g80::Integer N, g80::Integer R>
auto g80::IndexCombinator<N, R>::prev() -> bool {
    // If end is reached, set stack_ptr to last element of stack_ixs_;
    if (stack_ptr_ < 0) 
        stack_ptr_ = R - 1;

    // Early exit if start is reached
    if (stack_ixs_[stack_ptr_] == stack_ptr_)
        return false;

    // Expecting stack_ptr to be R - 1 at this point
    int last = stack_ixs_[stack_ptr_];
    while (stack_ptr_ > 0 && stack_ixs_[stack_ptr_] - 1 == stack_ixs_[stack_ptr_ - 1]) {
        last = stack_ixs_[stack_ptr_ - 1];
        --stack_ptr_;
    }

    stack_ixs_[stack_ptr_] = --last;
    if (stack_ptr_ != R - 1) {
        ++stack_ptr_;
        while (stack_ptr_ < R)
            stack_ixs_[stack_ptr_++] = max(stack_ptr_);
        
        stack_ptr_ = R - 1;
    }

    return true;
}
