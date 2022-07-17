#ifndef INDEX_COMBINATOR_HPP
#define INDEX_COMBINATOR_HPP

#include <cstdint>

namespace g80 {

    template<typename int_type>
    class index_combinator {

    /**
     * Iterator for 
     * combinations
     * 
     */

    private:

        struct iterator {
            private:
                int_type *p_;
            public:
                iterator(int_type *p) : p_(p) {}
                auto operator*() -> int_type & {return *p_;}
                auto operator->() -> int_type * {return p_;}
                auto operator++() -> iterator & {++p_; return *this;} 
                auto operator++(int) -> iterator & {iterator it = *this; ++p_; return it;} 
                friend auto operator==(const iterator &lhs, const iterator &rhs) -> bool {return lhs.p_ == rhs.p_;}
                friend auto operator!=(const iterator &lhs, const iterator &rhs) -> bool {return lhs.p_ != rhs.p_;}
        };

    /**
     * Private vars, helpers, 
     * constructors, destructors and assignments
     * 
     */

    private:

        int_type n_, r_, ix_;
        int_type *stacks_;

        inline auto max(int_type ix) -> int_type {return n_ - r_ + ix;}
        inline auto reset_stacks() -> void {for (int_type i = 0; i < n_; ++i) stacks_[i] = i;}

    public:

        index_combinator(int_type n, int_type r) : n_(n), r_(r), ix_(r_ - 1), stacks_(new int_type[n]) {reset_stacks();}
        ~index_combinator() {delete []stacks_;};
        index_combinator(const index_combinator &) = delete;
        index_combinator(index_combinator &&) = delete;
        auto operator=(const index_combinator &) -> index_combinator & = delete;
        auto operator=(index_combinator &&) -> index_combinator & = delete;

    /**
     * Public interfaces
     * 
     */

    public:

        inline auto size() const -> int_type {return n_;}
        inline auto r() const -> int_type {return r;}
        inline auto data() const -> const int * {return stacks_;}
        auto begin() -> iterator {return iterator(stacks_);}
        auto end() -> iterator {return iterator(stacks_ + r_);}
        inline auto reset() -> void {ix_ = r_ - 1; reset_stacks();}
        
        inline auto next() -> bool {
            if (ix_ < 0) return false;
            while (stacks_[ix_] == max(ix_)) if (--ix_ < 0) return false;
            if (ix_ < r_ - 1) {
                int_type last = ++stacks_[ix_];
                while (ix_ < r_ - 1) stacks_[++ix_] = ++last;
            } else {
                ++stacks_[ix_];
            }
            return true;        
        }

        inline auto prev() -> bool {
            if (ix_ < 0) ix_ = r_ - 1;
            if (stacks_[ix_] == ix_) return false;
            int_type last = stacks_[ix_];
            while (ix_ > 0 && stacks_[ix_] - 1 == stacks_[ix_ - 1]) {
                last = stacks_[ix_ - 1];
                --ix_;
            }
            stacks_[ix_] = --last;
            if (ix_ != r_ - 1) {
                ++ix_;
                while (ix_ < r_) stacks_[ix_++] = max(ix_);
                ix_ = r_ - 1;
            }
            return true;        
        }
    };
}

#endif