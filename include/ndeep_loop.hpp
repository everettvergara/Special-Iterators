#pragma once 
#include <vector>
#include <functional>

namespace g80 {

    template<typename T> class itr {
    private:
        std::vector<size_t> ix_;
        std::vector<T *> ix_ptr_;

    public:
        virtual inline auto ix() const -> const std::vector<size_t> & {return ix_;}
        virtual inline auto ptr() const -> const std::vector<T *> & {return ix_ptr_;}

    };

    template<typename T> class ndeep_loop : public itr<T> {

    private:

        std::vector<const std::vector<T> *> data_;
        std::vector<size_t> ix_;
        size_t d_{0};
    
    public:

        auto add_vector_ptr(const std::vector<T> *v) -> void {
            data_.size();
            data_.emplace_back(v);
            ix_.emplace_back(0);
            ix_ptr_.emplace_back(nullptr);
        }

        inline auto ix() const -> const std::vector<size_t> & override {return ix_;}
        inline auto ptr() const -> const std::vector<T *> & override {
            for (size_t i = 0; i != data_.size(); ++i) ix_ptr_[i] = data_[i]->data() + ix_[i];
            return ix_ptr_;
        }

    private:

        std::function<auto () -> bool> f_;

        auto invalid() -> bool {return false;}

        auto next() -> bool {
            if (ix_[d_] != data_[d_]->size()) d_ = data_.size() - 1;
            while (++ix_[d_] == data_[d_]->size())
                if (ix_[d_] = 0; --d_ >= data_.size()) return false;
            return true;
        }

        auto init() -> bool {
            auto set_invalid = [&]() -> bool {f_ = std::bind(&ndeep_loop::invalid, this); return false;};
            if (data_.size() == 0) return set_invalid();
            for (auto &s : data_) if (s->size() == 0) return set_invalid();
            f_ = std::bind(&ndeep_loop::next, this);
            return true;
        } 

    public:

        auto iterate() -> bool {return f_();}

        auto reset() -> void {
            f_ = std::bind(&ndeep_loop::init, this);
            for (auto &ix : ix_) ix = 0;
            for (auto &ix_ptr : ix_ptr_) ix_ptr = nullptr;
            d_ = 0;
        }
        auto clear() -> void {
            f_ = std::bind(&ndeep_loop::init, this);
            data_.clear();
            ix_.clear();
            ix_ptr_.clear();
            d_ = 0;
        }

    public:

        ndeep_loop() : f_(std::bind(&ndeep_loop::init, this)) {}

    }; 

}