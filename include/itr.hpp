#pragma once
#include <vector>
#include <functional>

namespace g80 {
    template<typename T> class itr {

    protected:

        // Indexes that points to the data to iterate
        std::vector<size_t> ix_;

        // Points to the values of the indexes to iterate
        std::vector<T *> ix_ptr_;

        // The function called when iterate() is called
        std::function<auto () -> bool> f_;

        // A function to always return false
        auto invalid() -> bool {return false;}

        // A virtual function to be called on next iteration
        virtual auto next() -> bool {return false;}

        // A virtual function to be called on the first iterate
        virtual auto init() -> bool {return false;}    
    
    public:

        itr(const std::function<auto () -> bool> &f) : f_(f) {}
        auto iterate() -> bool {return f_();}

        // A virtual function to reset. 
        // Reset means reset the values but no the allocation
        virtual auto reset() -> void {}

        // Clear means remove the allocations
        virtual auto clear() -> void {}

        // Add pointer to the data to iterate
        virtual auto add_vector_ptr(std::vector<T> *v) -> void {}

        // A reference to ix_;
        virtual inline auto ix() const -> const std::vector<size_t> & {return ix_;}

        // A reference to ix_ptr;
        virtual inline auto ptr() -> const std::vector<T *> & {return ix_ptr_;}        
    };
}