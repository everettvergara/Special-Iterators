#pragma once 

#include <vector>
#include <functional>

namespace g80 {
    
    template<typename T> class ndeep_loop {

    private:

        std::vector<const std::vector<T> *> data_;
        std::vector<size_t> ix_;
        size_t d_{0};
    
    public:

        auto add_vector_ptr(const std::vector<T> *v) -> void {
            data_.size();
            data_.emplace_back(v);
            ix_.emplace_back(0);
        }

        inline auto ix() const -> const std::vector<size_t> & {return ix_;}

    private:

        std::function<auto () -> bool> f_;

        auto invalid() -> bool {return false;}

        auto next() -> bool {
            // std::cout << "here1\n";
            if (ix_[d_] != data_[d_]->size()) d_ = data_.size() - 1;
            // std::cout << "here2\n";
            while (++ix_[d_] == data_[d_]->size())
                if (ix_[d_] = 0; --d_ >= data_.size()) return false;
            // std::cout << "here3\n";
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

    public:

        ndeep_loop() : f_(std::bind(&ndeep_loop::init, this)) {}

    }; 

}