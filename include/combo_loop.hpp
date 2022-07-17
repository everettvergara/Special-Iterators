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

        auto init() -> bool override {
            if (!r_) return false;
            auto set_invalid = [&]() -> bool {f_ = std::bind(&combo_loop::invalid, this); return false;};
            if (data_->size() == 0) return set_invalid();
            f_ = std::bind(&combo_loop::next, this);
            return true;
        } 

    public:

        combo_loop (size_t r) : itr<T>(std::bind(&combo_loop::init, this)), r_(r) {}

        auto reset() -> void override {
            for (size_t i = 0; i != r_; ++i) ix_[i] = i;
            f_ = std::bind(&combo_loop::init, this); 
            i_ = 0;
        }

        auto clear() -> void override {
            ix_.clear();
            ix_ptr_.clear();
            data_->clear();
            f_ = std::bind(&combo_loop::init, this); 
            i_ = 0;
            r_ = 0;
        }
        
        auto add_vector_ptr(std::vector<T> *v) -> void override {
            if (ix_.size()) return; 
            data_ = v;
            for (size_t i = 0; i != r_; ++i) {ix_.emplace_back(i); ix_ptr_.emplace_back(nullptr);}
        }

        inline auto change_r(size_t r) -> bool {
            if (r) return false;
            r_ = r;
            return true;
        }

        inline auto ix() const -> const std::vector<size_t> & override {return ix_;}
        
        inline auto ptr() -> const std::vector<T *> & override {
            for (size_t i = 0; i != r_; ++i) 
                ix_ptr_[i] = data_->data() + ix_[i]; 
            return ix_ptr_;
        }
    };
}