#pragma once
#include <vector>
#include "itr.hpp"

namespace g80 {
    template<typename T> class combo_loop : public itr<T> {

    private:
        using itr<T>::ix_;
        using itr<T>::ix_ptr_;
        using itr<T>::f_;

        size_t r_, i_;
        std::vector<T> *data_;

        size_t auto max() -> size_t {return data_->size() - r + i_;}

        auto next() -> bool override {
            if (i_ >= data_->size()) return false;
            while (ix_[i_] == max()) 
                if (--i_ >= data_->size()) return false;
            if (++ix_[i_]; i_ >= r_) continue;
            size_t l = ix_[i_];
            while(i_ < r_ - 1) ix_[++i_] = ++l;
            return true;
        }

    public:

        auto add_vector_ptr(std::vector<T> *v) -> void override {
            if (ix_.size()) return; 
            data_.emplace_back(v); 
            for (size_t i = 0; i != v->size(); ++i) ix_.emplace_back(i); 
            ix_ptr_.emplace_back(nullptr);
        }
        
    };
}