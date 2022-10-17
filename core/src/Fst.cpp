#include <Fst.h>

#include <Louds/Dense.h>
#include <Louds/Sparse.h>
#include <PrefixTree/Tree.h>

#include <utils/utils.h>

#include <iostream>

namespace {

template<typename Louds>
void insertToLouds(Louds *louds,
                   Surf::PrefixTree::Node *node,
                   u64 lvl,
                   u64 cur_lvl = 0) {
    if (cur_lvl > lvl) return;
    if (cur_lvl < lvl) {
        if (!node->hasChild()) {
            return;
        }
        for (auto &child : *node->data) {
            if (child) insertToLouds(louds, child, lvl, cur_lvl + 1);
        }
        return;
    }

    if (node->hasChild()) {
        louds->addNode(node);
    }
}

} // namespace

namespace Surf {

Fst::Fst(const std::vector<std::pair<key_t, value_t>> &data) {
    PrefixTree::Tree buf_tree;
    for (auto &&pair : data) {
        buf_tree.insert(pair.first, pair.second);
    }

    m_dense = new Dense();

    u64 lvl = 0;
    for (u64 dense_lvl = buf_tree.size() / 2; lvl < dense_lvl; ++lvl) {
        // std::cout << "Insert to dense lvl " << lvl << '\n';
        insertToLouds(m_dense, buf_tree.head(), lvl);
    }

    m_sparse = new Sparse(m_dense->getSparseChild(), lvl);

    std::cout << "Sparse child " << m_dense->getSparseChild() << '\n';

    for (u64 sparse_lvl = buf_tree.size(); lvl < sparse_lvl; ++lvl) {
        // std::cout << "Insert to sparse lvl " << lvl << '\n';
        insertToLouds(m_sparse, buf_tree.head(), lvl);
    }
}

Fst::~Fst() {
    delete m_dense;
    delete m_sparse;
}

value_t *Fst::exactKeySearch(const key_t &key) {
    u64 pos = 0;
    // try to find value in dense & get dense_pos
    value_t *ans = m_dense->exactKeySearch(key.begin(), key.end(), pos);
    if (ans) return ans;

    if(pos == std::numeric_limits<u64>::max()) {
        return nullptr;
    }

    ans = m_sparse->exactKeySearch(key.begin(), key.end(), pos);
    return ans;
}

} // namespace Surf