#pragma once

#include <vector>

#include <surfTypes.h>
#include <PrefixTree/Tree.h>

namespace Surf { inline namespace Louds {

class Dense {
public:
    void addNode(Tree::Node *node) {
        std::vector<bool> m_label(SIZE);
        std::vector<bool> m_has_child(SIZE);
        b32 m_is_prefix_key = false;
        std::vector<value_t> m_values;
        if(node->hasChild()) {
            auto data = *node->data;
            for(auto&& child : data) {
                m_label[child->symb] = true;
                if(m_has_child[child->symb] = child->hasChild()) {
                    else 
                }
            }
        } else {
            m_is_prefix_key = true;
        }
    }

private:
    std::vector<bool> m_label;
    std::vector<bool> m_has_child;
    std::vector<bool> m_is_prefix_key;
    std::vector<value_t> m_values;

};

}} // namespace Surf::Louds