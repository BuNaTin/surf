#pragma once

#include <surfTypes.h>

#include <vector>

namespace Surf {

// predefinition
inline namespace PrefixTree {
struct Node;
}

inline namespace Louds {

class Sparse {
public:
    void addNode(PrefixTree::Node *node);
    value_t *exactKeySearch(std::string::const_iterator it,
                            std::string::const_iterator end,
                            const u64 sparse_pos);

    Sparse(u64 dense_has_child, u64 tree_lvl) : m_dense_has_child(dense_has_child), m_tree_lvl(tree_lvl) {}

private:
    std::vector<char> m_label;
    std::vector<bool> m_has_child;
    std::vector<bool> m_louds;
    std::vector<value_t> m_values;
    u64 m_dense_has_child;
    u64 m_tree_lvl;
};

} // namespace Louds
} // namespace Surf