#pragma once

#include <surfTypes.h>

#include <vector>

namespace Surf { 

// predefinition
inline namespace PrefixTree {
struct Node;
}

inline namespace Louds {

class Dense {
public:
    void addNode(PrefixTree::Node *node);
    value_t *exactKeySearch(std::string::const_iterator it,
                            std::string::const_iterator end,
                            const u64 dense_pos = 0);

private:
    std::vector<bool> m_label;
    std::vector<bool> m_has_child;
    std::vector<bool> m_is_prefix_key;
    std::vector<value_t> m_values;
};
}} // namespace Surf::Louds