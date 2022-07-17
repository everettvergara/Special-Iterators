/*
 *  IndexCombinator Class. "Combinates" indexes.
 *  Copyright (C) 2022 Everett Gaius S. Vergara
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *	
 */

#ifndef _INDEX_COMBINATOR_H_
#define _INDEX_COMBINATOR_H_

#include <vector>
#include <cstdint>

namespace g80 {
    using Integer = int32_t;

    using StackIxs = std::vector<Integer>; 

    class IndexCombinator {
    public:
        IndexCombinator(Integer N, Integer R);

        // Copy not allowed since N_ and R_ are const
        auto operator=(const IndexCombinator &) = delete;

        auto reset() -> void;

        inline auto get() const -> const StackIxs & {
            return stack_ixs_;
        }

        inline auto N() const -> Integer {
            return N_;
        }

        inline auto R() const -> Integer {
            return R_;
        }

        auto next() -> bool;
        auto prev() -> bool;

    private:
        const Integer N_, R_;
        StackIxs stack_ixs_;
        Integer stack_ptr_;

        inline auto max(Integer ix) -> Integer {
            return N_ - R_ + ix;
        }
    };
}

#endif 
