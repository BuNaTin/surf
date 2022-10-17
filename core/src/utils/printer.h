#pragma once

#include <vector>
#include <iostream>

inline namespace utils {

template<typename T>
void printer(const char* str, const std::vector<T> &v, const char sep = '\0') {
    std::size_t i = 0;
    std::cout << "Vector " << str << ':';
    for(T b : v) {
        if(i % 16 == 0) {
            std::cout << '\n' << i << ":";
        }
        ++i;
        std::cout << b << sep;
    }
    std::cout << '\n';
}

}