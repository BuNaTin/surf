#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <Fst.h>
#include <surfTypes.h>

#include <iostream>

void test(Surf::Fst &fst,
          const std::vector<Surf::key_t> &keys,
          const std::vector<std::pair<Surf::key_t, Surf::value_t>>
                  &stored) {
    using Surf::key_t;
    using Surf::value_t;

    std::cout << "Run tests\n";

    u64 i = 0, size = keys.size();

    std::string passed =
            "Passed " + std::to_string(i) + "/" + std::to_string(size);

    for (const auto &key : keys) {
        // if not find
        auto it = std::find_if(
                stored.begin(), stored.end(), [&key](const auto &pair) {
                    return pair.first == key;
                });
        if (it == stored.end()) {
            if (fst.exactKeySearch(key) != nullptr) {
                std::cerr << "\nAssertion failed at test " << i
                          << "\nFst should not contain key " << key
                          << '\n';
            }
        } else {
            value_t *v = fst.exactKeySearch(key);
            if (v == nullptr) {
                std::cerr << "\nAssertion failed at test " << i
                          << "\nFst should contain key " << key << '\n';
                continue;
            }
            if (*v != it->second) {
                std::cerr << "\nAssertion failed at test " << i
                          << "\nValue of key " << key
                          << " is wrong (it should be " << it->second
                          << " not " << *v << ")\n";
            }
        }

        ++i;
        passed = "Passed " + std::to_string(i) + "/" +
                 std::to_string(size);
        std::cout << passed << std::endl;
    }
    std::cout << std::endl;
}