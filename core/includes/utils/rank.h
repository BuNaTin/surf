#pragma once

#include <types.h>

inline namespace utils {

template<b32 bool_value>
u64 rank(const std::vector<bool>& v, u64 pos) {
    assert(pos < v.size() && "Rank pos higher than v size");
    u64 ans = 0;
    for(u64 i = 0; i <= pos; ++i) {
        ans += (v[i] == bool_value);
    }
    return ans;
}

}