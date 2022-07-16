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
}