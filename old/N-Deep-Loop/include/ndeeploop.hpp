#pragma once
#include <vector>
#include <functional>

namespace g80 {

    template<typename T> using to_iter_data = std::vector<const std::vector<T> *>;

    template<typename T> class loop_struct {

    protected:

        to_iter_data<T> data_;
        std::vector<const T *> begin_;
        std::vector<const T *> ptr_;
        std::vector<const T *> end_;
    
        auto loop_struct_init() -> void {ixs_.resize(data_.size(), 0);}
    
    public:

        inline auto ix_begin() const -> const std::vector<const T *> & {return begin_;}
        inline auto ix_ptr() const -> const std::vector<const T *> & {return ptr_;}
        inline auto ix_end() const -> const std::vector<const T *> & {return end_;}


    };

    template<typename T> class ndeep_loop : public loop_struct<T> {

    private:

        using loop_struct<T>::data_;
        using loop_struct<T>::begin_;
        using loop_struct<T>::ptr_;
        using loop_struct<T>::end_;
        using loop_struct<T>::loop_struct_init;

    private:
        
        size_t d_{0};
        std::vector<size_t> ixs_;
        std::function<auto (const loop_struct<T> &) -> void> f_before_{nullptr};
        std::function<auto (const loop_struct<T> &) -> void> f_after_{nullptr};

    private:

        std::function<auto () -> bool> f_;

        auto f_next() -> bool {
            if (ptr_[d_] != end_[d_]) d_ = data_.size() - 1;
            while (++ptr_[d_] == end_[d_])
                if (ptr_[d_] = begin_[d_]; --d_ >= data_.size()) return false;
            return true;
        }

        auto f_next_wafter() -> bool {
            if (ptr_[d_] != end_[d_]) d_ = data_.size() - 1;
            while (++ptr_[d_] == end_[d_]) {
                f_after_(dynamic_cast<loop_struct<T> &>(*this));
                if (ptr_[d_] = begin_[d_]; --d_ >= data_.size()) return false;
            }
            return true;
        }

        auto f_next_wbefore() -> bool {
            if (ptr_[d_] != end_[d_]) d_ = data_.size() - 1;
            while (++ptr_[d_] == end_[d_]) {
                ptr_[d_] = begin_[d_]; --d_;
                if (d_ < data_.size() && ptr_[d_] + 1 != end_[d_]) f_before_(dynamic_cast<loop_struct<T> &>(*this)); 
                else if (d_ >= data_.size()) return false;
            }
            return true;
        }

        auto f_next_wbeforeafter() -> bool {
            if (ptr_[d_] != end_[d_]) d_ = data_.size() - 1;
            while (++ptr_[d_] == end_[d_]) {
                f_after_(dynamic_cast<loop_struct<T> &>(*this)); ptr_[d_] = begin_[d_]; --d_;
                if (d_ < data_.size() && ptr_[d_] + 1 != end_[d_]) f_before_(dynamic_cast<loop_struct<T> &>(*this)); 
                else if (d_ >= data_.size()) return false;
            }
            return true;
        }

        auto f_invalid() -> bool {return false;}

        auto f_init_check() -> bool {
            loop_struct_init();
            
            auto set_invalid = [&]() -> bool {f_ = std::bind(std::bind(&ndeep_loop::f_invalid, this)); return false;};
            if (data_.size() == 0) return set_invalid(); 
            for (auto &s : data_) if (s->size() == 0) return set_invalid();
            for (auto &s : data_) {ptr_.emplace_back(s->data()); begin_.emplace_back(s->data()); end_.emplace_back(s->data() + s->size());}
            
            auto set_f_before = [&]() -> void {
                for (d_ = 0; d_ < data_.size(); ++d_) f_before_(dynamic_cast<loop_struct<T> &>(*this)); --d_;
                if (f_after_ != nullptr) f_ = std::bind(std::bind(&ndeep_loop::f_next_wbeforeafter, this));
                else f_ = std::bind(std::bind(&ndeep_loop::f_next_wbefore, this));
            };
            if (f_before_) set_f_before();
            else if (f_after_) f_ = std::bind(std::bind(&ndeep_loop::f_next_wafter, this));
            else f_ = std::bind(std::bind(&ndeep_loop::f_next, this)); 

            return true;
        }

    public:

        ndeep_loop(
            const std::function<auto (const loop_struct<T> &) -> void> f_before = nullptr,
            const std::function<auto (const loop_struct<T> &) -> void> f_after = nullptr) : 
            f_before_(f_before),  f_after_(f_after), f_(std::bind(&ndeep_loop::f_init_check, this)) {}

        auto ixs() ->  const std::vector<size_t> & {for (size_t i = 0; i < ixs_.size(); ++i) ixs_[d_] = ptr_[d_] - data_[d_]->data(); return ixs_;}
        
        inline auto add_vector(const std::vector<T> *vec) -> bool {
            if (ixs_.size()) return false;
            data_.emplace_back(vec);
            return true;
         }
         
        inline auto iterate() -> bool {return f_();}
    };

}