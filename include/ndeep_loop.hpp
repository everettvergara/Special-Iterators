#pragma once 

#include <vector>
#include <functional>

namespace g80 {
    
    template<typename T> class ndeep_loop {

    private:

        std::vector<const std::vector<T> *> data_;
        std::vector<size_t> ix_;
        size_t d_;
    
    public:

        auto add_vector_ptr(const std::vector<T> *v) -> void {
            auto s = data_.size();
            data_.emplace_back(v);
            ix_[s] = 0;
        }

        inline auto ix() const -> const std::vector<const size_t> & {return ix_;}

    public:

        ndeep_loop() {}

        auto next() -> bool {
            if (ix_[d_] != data_[d_]->size()) d_ = data_.size() - 1;
            while (++ix_[d_] == data_[d_]->size())
                if (ix_[d_] = 0; --d_ >= data_.size()) return false;
            return true;
        }

        auto iterate() -> bool {
            return next();
        }
    }; 

}