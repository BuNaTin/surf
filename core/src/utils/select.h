#pragma once

#include <algorithm>
#include <types.h>
#include <vector>

inline namespace utils {

template<b32 bool_value>
u64 select(const std::vector<bool> &v, u64 count) {
    assert(0 < count && count <= v.size() &&
           "Select wrong count to select");

    auto check = [&count](bool value) {
        if (value == bool_value) --count;
        return !count;
    };
    return std::distance(v.begin(),
                         std::find_if(v.begin(), v.end(), check));
}

} // namespace utils