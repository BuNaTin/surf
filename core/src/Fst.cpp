#include <Fst.h>

#include <Louds/Dense.h>
#include <PrefixTree/Tree.h>

#include <iostream>

namespace Surf {

Fst::Fst(const std::vector<std::pair<key_t, value_t>> &data) {
    PrefixTree::Tree buf_tree;
    for (auto &&pair : data) {
        buf_tree.insert(pair.first, pair.second);
    }

    m_dense = new Dense();
    for (u64 lvl = 0; lvl < buf_tree.size(); ++lvl) {
        // std::cout << "Insert to lvl " << lvl << '\n';
        insertToDense(buf_tree.head(), lvl);
    }
}

Fst::~Fst() {
    delete m_dense;
}

value_t *Fst::exactKeySearch(const key_t &key) {
    return m_dense->exactKeySearch(key.begin(), --key.end());
}

void Fst::insertToDense(PrefixTree::Node *node, u64 lvl, u64 cur_lvl) {
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
        m_dense->addNode(node);
    }
}

} // namespace Surf