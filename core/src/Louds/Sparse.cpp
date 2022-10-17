#include <Louds/Sparse.h>

#include <PrefixTree/Node.h>
#include <PrefixTree/Tree.h>
#include <surfTypes.h>
#include <utils/utils.h>

#include <algorithm>
#include <vector>

#include <iostream>

namespace Surf { inline namespace Louds {

void Sparse::addNode(PrefixTree::Node *node) {
    if (!node->hasChild()) {
        // //// std::cout << "No child [" << node->value << "]\n";
        return;
    }
    auto data = *node->data;
    bool is_louds = true;
    for (u64 i = 0; i < SIZE; ++i) {
        if (data[i]) {
            // std::cout << "Sparse: " << (char)i << ':' <<
            // m_label.size()
            //   << '\n';

            m_louds.push_back(is_louds);
            if (is_louds) is_louds = false;

            m_label.push_back(i);
            m_has_child.push_back(data[i]->hasChild());
            if (!data[i]->hasChild()) {
                // std::cout << "Value " << data[i]->value << " at pos "
                //   << m_values.size() << '\n';
                m_values.push_back(data[i]->value);
            }
        }
    }
}
value_t *Sparse::exactKeySearch(std::string::const_iterator it,
                                std::string::const_iterator end,
                                const u64 sparse_pos) {

    // printer("Label", m_label);
    // printer("HasCh", m_has_child);
    // printer("Loud", m_louds);

    // // std::cout << "Start sparse from " << *(it + m_tree_lvl) <<
    // '\n';

    u64 pos = sparse_pos;
    for (it += m_tree_lvl; it != end && pos < m_label.size(); ++it) {
        // std::cout << "Sparse at " << *it << '\n';
        while (m_label[pos] != *it && pos < m_label.size()) {
            // std::cout << "Sparse node " << pos << " value ["
            //   << m_label[pos] << "] it [" << *it << "]\n";
            ++pos;
            if (m_louds[pos]) {
                // std::cout << "Gone to wrong " << pos << "\n";
                return nullptr;
            }
        }
        if (m_has_child[pos]) {
            // std::cout << "Go down from " << pos << " at "
            //   << rank<1>(m_has_child, pos) + m_dense_has_child
            //   << '\n';

            pos = select<1>(m_louds,
                            rank<1>(m_has_child, pos) +
                                    m_dense_has_child);

            // std::cout << "Go to child " << m_label[pos] << '\n';
        }
    }
    if (it != end || pos == m_label.size()) {
        // std::cout << "At end\n";
        return nullptr;
    }

    return &m_values[pos - rank<1>(m_has_child, pos)];
}
}} // namespace Surf::Louds