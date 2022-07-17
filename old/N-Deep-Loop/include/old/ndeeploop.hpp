#ifndef NDEEPLOOP_HPP
#define NDEEPLOOP_HPP

#include <functional>

namespace g80 {

    template<typename T>
    class ndeeploop {
    private:

        const std::vector<std::vector<T>> &to_iter_;
        std::vector<size_t> s_;
        std::vector<size_t> ixs_;

        size_t l_, i_;
        std::function<auto () -> bool> f_;

        auto f_next() -> bool {
            if (ixs_[i_] != to_iter_[s_[i_]].size()) i_ = l_;
            while (++ixs_[i_] == to_iter_[s_[i_]].size()) 
                if (ixs_[i_] = 0; --i_ >= s_.size()) return false;
            return true;
        }

        auto f_invalid() -> bool {
            return false;
        }

        auto f_init_check() -> bool {
            if (s_.size() == 0) {
                f_ = std::bind(std::bind(&ndeeploop::f_invalid, this));
                return false;
            }

            for (auto &s : s_) {
                if (to_iter_[s].size() == 0) {
                    f_ = std::bind(std::bind(&ndeeploop::f_invalid, this));
                    return false;
                }
            }

            f_ = std::bind(std::bind(&ndeeploop::f_next, this));
            return true;
        }

    public:

        ndeeploop(const std::vector<std::vector<T>> &to_iter) : 
            to_iter_(to_iter), ixs_(to_iter_.size(), 0), l_(to_iter_.size() - 1), i_(l_), f_(std::bind(&ndeeploop::f_init_check, this)) {

            s_.reserve(to_iter_.size());
            for (size_t i = 0; i < to_iter_.size(); ++i) s_.emplace_back(i);
        }

        ndeeploop(const std::vector<std::vector<T>> &to_iter, const std::vector<size_t> &s) : 
            to_iter_(to_iter), s_(s), ixs_(s.size(), 0), l_(s.size() - 1), i_(l_), f_(std::bind(&ndeeploop::f_init_check, this)) {}

        inline auto ixs() const -> const std::vector<size_t> & {return ixs_;}
        inline auto is_valid() -> bool {return f_();}
    };

}

#endif 