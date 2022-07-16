#pragma once 
#include <vector>
#include <functional>

namespace g80 {

    template<typename T> class itr {

    protected:

        std::vector<size_t> ix_;
        std::vector<T *> ix_ptr_;
        std::function<auto () -> bool> f_;
        auto invalid() -> bool {return false;}
        virtual auto next() -> bool {return false;}        
        virtual auto init() -> bool {return false;}    
    
    public:

        itr(const std::function<auto () -> bool> &f) : f_(f) {}
        auto iterate() -> bool {return f_();}
        virtual auto reset() -> void {for (auto &ix : ix_) ix = 0; for (auto &ix_ptr : ix_ptr_) ix_ptr = nullptr;}
        virtual auto clear() -> void {ix_.clear(); ix_ptr_.clear();}
        virtual auto add_vector_ptr(std::vector<T> *v) -> void {}
        virtual inline auto ix() const -> const std::vector<size_t> & {return ix_;}
        virtual inline auto ptr() -> const std::vector<T *> & {return ix_ptr_;}        

    };

    template<typename T> class ndeep_loop : public itr<T> {

    private:

        using itr<T>::ix_;
        using itr<T>::ix_ptr_;
        std::vector<std::vector<T> *> data_;
        size_t d_{0};
    
    public:

        auto add_vector_ptr(std::vector<T> *v) -> void override {
            data_.size();
            data_.emplace_back(v);
            ix_.emplace_back(0);
            ix_ptr_.emplace_back(nullptr);
        }
        inline auto ix() const -> const std::vector<size_t> & override {return ix_;}
        inline auto ptr() -> const std::vector<T *> & override {
            for (size_t i = 0; i != data_.size(); ++i) 
                ix_ptr_[i] = data_[i]->data() + ix_[i];
            return ix_ptr_;
        }

    private:

        using itr<T>::f_;
        
        auto next() -> bool override {
            if (ix_[d_] != data_[d_]->size()) d_ = data_.size() - 1;
            while (++ix_[d_] == data_[d_]->size())
                if (ix_[d_] = 0; --d_ >= data_.size()) return false;
            return true;
        }

        auto init() -> bool override {
            auto set_invalid = [&]() -> bool {f_ = std::bind(&ndeep_loop::invalid, this); return false;};
            if (data_.size() == 0) return set_invalid();
            for (auto &s : data_) if (s->size() == 0) return set_invalid();
            f_ = std::bind(&ndeep_loop::next, this);
            return true;
        } 

    public:

        auto reset() -> void override {
            itr<T>::reset();
            f_ = std::bind(&ndeep_loop::init, this);
            d_ = 0;
        }

        auto clear() -> void override {
            itr<T>::clear();
            f_ = std::bind(&ndeep_loop::init, this);
            data_.clear();        
            d_ = 0;
        }

        ndeep_loop() : itr<T>(std::bind(&ndeep_loop::init, this)) {}

    }; 

}