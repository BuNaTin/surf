#pragma once

#include <array>
#include <iostream>
#include <optional>

#include <surfTypes.h>

namespace Surf { inline namespace PrefixTree {

struct Node {
    /* NEVER CONTAIN CHILDREN AT '\0' */
    std::optional<std::array<Node *, SIZE>> data;
    value_t value;

    Node() {}

    bool hasChild() { return !!data; }

    Node *child(u8 symb) {
        if (!data) {
            std::cerr << "Child [" << symb << "] of nullopt data\n";
            return nullptr;
        }
        return (*data)[symb];
    }

    ~Node() {
        if (!data) return;
        for (auto &&node : *data)
            delete node;
    }
};

}} // namespace Surf::PrefixTree