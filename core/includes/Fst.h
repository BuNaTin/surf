#pragma once

#include <vector>

#include <Louds/Dense.h>
#include <surfTypes.h>

#include <iostream>

namespace Surf {

class Fst {
public:
    Fst(const std::vector<std::pair<key_t, value_t>> &data) {
        PrefixTree::Tree buf_tree;
        for (auto &&pair : data) {
            buf_tree.insert(pair.first, pair.second);
        }

        for (u64 lvl = 0; lvl < buf_tree.size(); ++lvl) {
            std::cout << "Insert to lvl " << lvl << '\n';
            insertToDense(buf_tree.m_head, lvl);
        }
    }

    value_t *exactKeySearch(const key_t &key) {
        return m_dense.exactKeySearch(key.begin(), --key.end());
    }

private:
    void insertToDense(Tree::Node *node, u64 lvl, u64 cur_lvl = 0) {
        if (cur_lvl > lvl) return;
        if (cur_lvl < lvl) {
            if (!node->hasChild()) {
                return;
            }
            for (auto &child : *node->data) {
                if (child) insertToDense(child, lvl, cur_lvl + 1);
            }
            return;
        }

        if (node->hasChild()) {
            m_dense.addNode(node);
        }
    }

private:
    Louds::Dense m_dense;
    // Louds::Sparce;
};

} // namespace Surf