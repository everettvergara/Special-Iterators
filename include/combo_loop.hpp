#pragma once
#include <vector>
#include "itr.hpp"

namespace g80 {

    template<typename T> class combo_loop : public itr<T> {

    private:
        using itr<T>::ix_;
        using itr<T>::ix_ptr_;
        using itr<T>::f_;

        size_t r_;
        size_t i_{0};
        std::vector<T> *data_{nullptr};

        inline auto max() -> size_t {return data_->size() - r_ + i_;}

        auto next() -> bool override {
            if (i_ >= r_) return false;
            while (ix_[i_] == max()) if (--i_ >= r_) return false;
            if (++ix_[i_]; i_ >= r_) return true;
            size_t l = ix_[i_];
            while(i_ < r_ - 1) ix_[++i_] = ++l;
            return true;
        }

    public:

        combo_loop (size_t r) : itr<T>(std::bind(&combo_loop::next, this)), r_(r) {}

        auto add_vector_ptr(std::vector<T> *v) -> void override {
            if (ix_.size()) return; 
            data_ = v;
            for (size_t i = 0; i != r_; ++i) ix_.emplace_back(i); 
            ix_ptr_.emplace_back(nullptr);
        }
        
    };
}