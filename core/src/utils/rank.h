#pragma once

#include <algorithm>
#include <numeric>
#include <types.h>
#include <vector>

inline namespace utils {

template<b32 bool_value>
u64 rank(const std::vector<bool> &v, u64 pos) {
    assert(pos < v.size() && "Rank pos higher than v size");
    u64 rank1 = std::accumulate(v.begin(), v.begin() + pos + 1, 0ull);
    if (!bool_value) {
        rank1 = pos - rank1;
    }
    return rank1;
}

template<b32 bool_value>
u64 rank(std::vector<bool>::const_iterator begin,
         std::vector<bool>::const_iterator end) {
    u64 rank1 = std::accumulate(begin, end, 0ull);
    if (!bool_value) {
        rank1 = std::distance(begin, end) - rank1;
    }
    return rank1;
}

} // namespace utils