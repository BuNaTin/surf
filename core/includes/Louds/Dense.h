#pragma once

#include <PrefixTree/Tree.h>
#include <surfTypes.h>
#include <utils/utils.h>

#include <vector>

#include <iostream>

namespace Surf { inline namespace Louds {

class Dense {
public:
    void addNode(Tree::Node *node) {
        std::cout << "Add node to " << m_label.size() << "\n";
        if (!node->hasChild()) {
            std::cout << "No child [" << node->value << "]\n";
            return;
        }
        auto data = *node->data;
        for (u64 i = 0; i < SIZE; ++i) {
            if (data[i]) {
                std::cout << (char)i << ':' << m_label.size() << '\n';
                m_label.push_back(true);
                m_has_child.push_back(data[i]->hasChild());
                if (!data[i]->hasChild()) {
                    m_values.push_back(data[i]->value);
                }
            } else {
                m_label.push_back(false);
                m_has_child.push_back(false);
            }
        }
        // for (auto &&child : data) {
        //     b_label.push_back(child != nullptr);
        //     if(child == nullptr) {
        //         b_has_child.push_back(false);
        //         continue;
        //     }
        //     b_has_child.push_back(child->hasChild());
        //     if (!child->hasChild()) {
        //         m_values.push_back(child->value);
        //     }
        // }
        if (data[Tree::SPECIAL_CHAR]) {
            m_is_prefix_key.push_back(true);
        } else {
            m_is_prefix_key.push_back(false);
        }
    }
    value_t *exactKeySearch(std::string::const_iterator it,
                            std::string::const_iterator end,
                            const u64 dense_pos = 0) {
        // printer("labels", m_label);
        // printer("values", m_values, ',');

        u64 new_pos = dense_pos + *it;
        std::cout << "Exact [" << new_pos << "] at dense " << dense_pos
                  << " and symb " << (int)*it << '\n';
        if (!m_label[new_pos]) {
            return nullptr;
        }
        if (it == end) {
            if (m_has_child[new_pos]) {
                if (m_label[dense_pos + Tree::SPECIAL_CHAR]) {
                    std::cout << "Go to '$'\n";
                    new_pos = SIZE * rank<1>(m_has_child, dense_pos + Tree::SPECIAL_CHAR);
                } else {
                    return nullptr;
                }
            }
            u64 value_ind = rank<1>(m_label, new_pos) -
                            rank<1>(m_has_child, new_pos) +
                            rank<1>(m_is_prefix_key, new_pos / 256) - 1;
            std::cout << "Value index: " << value_ind << '\n';
            return &m_values[value_ind];
        }
        if (m_has_child[new_pos]) {
            std::cout << "Go down to " << rank<1>(m_has_child, new_pos)
                      << "\n";
            return exactKeySearch(
                    ++it, end, SIZE * rank<1>(m_has_child, new_pos));
            // go down
        }
        return nullptr;
    }

private:
    std::vector<bool> m_label;
    std::vector<bool> m_has_child;
    std::vector<bool> m_is_prefix_key;
    std::vector<value_t> m_values;
};

}} // namespace Surf::Louds