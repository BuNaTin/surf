#include <Louds/Dense.h>

#include <PrefixTree/Node.h>
#include <PrefixTree/Tree.h>
#include <surfTypes.h>
#include <utils/utils.h>

#include <algorithm>
#include <vector>

#include <iostream>

namespace Surf { inline namespace Louds {

void Dense::addNode(PrefixTree::Node *node) {
    // //std::cout << "Add node to " << m_label.size() << "\n";
    if (!node->hasChild()) {
        // //std::cout << "No child [" << node->value << "]\n";
        return;
    }
    const auto &data = *node->data;
    if (data[Tree::SPECIAL_CHAR]) {
        m_values.push_back(data[Tree::SPECIAL_CHAR]->value);
        m_is_prefix_key.push_back(true);
    } else {
        m_is_prefix_key.push_back(false);
    }
    for (u64 i = 0; i < SIZE; ++i) {
        if (data[i] && i != Tree::SPECIAL_CHAR) {
            std::cout << "Dense: " << (char)i << ':' << m_label.size()
                      << '\n';

            m_label.push_back(true);
            m_has_child.push_back(data[i]->hasChild());
            if (!data[i]->hasChild()) {
                // //std::cout << "Value [" << m_values.size()
                //           << "]: " << data[i]->value << '\n';
                m_values.push_back(data[i]->value);
            }
        } else {
            m_label.push_back(false);
            m_has_child.push_back(false);
        }
    }
}
value_t *Dense::exactKeySearch(std::string::const_iterator it,
                               std::string::const_iterator end,
                               u64 &dense_pos) {
    // printer("labels", m_label);
    // printer("values", m_values, ',');
    // printer("pre-key", m_is_prefix_key);

    auto assert_no_down = [this, &dense_pos](const char c) -> bool {
        dense_pos += c;
        if (!m_label[dense_pos]) {
            return true;
        }
        if (m_has_child[dense_pos]) {
            dense_pos = SIZE * rank<1>(m_has_child, dense_pos);
            return false;
        }
        return true;
    };

    auto check = std::find_if(it, --end, assert_no_down);
    if (check != end) {
        if (dense_pos > SIZE) {
            dense_pos = (dense_pos / SIZE) - m_is_prefix_key.size();
        } else {
            dense_pos = std::numeric_limits<u64>::max();
        }
        return nullptr;
    }
    dense_pos += *end;

    // if do not has label at end -> NULL
    if (!m_label[dense_pos]) {
        dense_pos = std::numeric_limits<u64>::max();
        return nullptr;
    }

    auto get_value_ind = [this](const u64 dense_pos) {
        return rank<1>(m_label, dense_pos) -
               rank<1>(m_has_child, dense_pos) +
               rank<1>(m_is_prefix_key, dense_pos / SIZE);
    };

    // no child - so contain value
    if (!m_has_child[dense_pos]) {
        u64 value_ind = get_value_ind(dense_pos) - 1;
        return &m_values[value_ind];
    } else {
        // current end is prefix
        if (m_is_prefix_key[rank<1>(m_has_child, dense_pos)]) {
            u64 value_ind = get_value_ind(dense_pos);
            return &m_values[value_ind];
        }
    }

    return nullptr;
}

// TODO
u64 Dense::getSparseChild() {
    u64 ans = 0;
    for (u64 pos = 0, end = m_label.size() / SIZE; pos < end; ++pos) {
        for (bool has_child : m_has_child) {
            if (has_child &&
                rank<1>(m_has_child, SIZE * (pos + 1) - 1) >= end) {
                ans = pos;
                pos = end;
                break;
            }
        }
    }
    return rank<1>(m_has_child.begin() + ans * SIZE, m_has_child.end());
}

}} // namespace Surf::Louds