#include <PrefixTree/Tree.h>

namespace Surf { inline namespace PrefixTree {

bool Tree::insert(const key_t &str, const value_t value) {
    Node *cur_node = m_head;
    for (auto symb : str) {
        // std::cout << "Insert " << symb << '\n';
        if (!cur_node->data) {
            cur_node->data = std::array<Node *, SIZE>();
        }

        if (cur_node->child(symb) == nullptr) {
            (*cur_node->data)[symb] = new Node;
        }
        cur_node = cur_node->child(symb);
    }
    if (cur_node->hasChild()) {
        if (cur_node->child(SPECIAL_CHAR) == nullptr) {
            (*cur_node->data)[SPECIAL_CHAR] = new Node;
        }
        cur_node = cur_node->child(SPECIAL_CHAR);

        m_size = std::max(m_size, str.size() + 1);
    } else {
        m_size = std::max(m_size, str.size());
    }
    cur_node->value = value;
    return true;
}

bool Tree::find(const std::string &str, u64 &value) {
    Node *cur_node = m_head;
    auto it = str.begin(), end = str.end();
    for (; it != end && cur_node != nullptr; ++it) {
        // std::cout << "GO : " << *it << '\n';
        cur_node = cur_node->child(*it);
    }
    if (cur_node != nullptr &&
        cur_node->child(SPECIAL_CHAR) != nullptr) {
        cur_node = cur_node->child(SPECIAL_CHAR);
    }
    if (it == end && cur_node != nullptr && !cur_node->hasChild()) {
        value = cur_node->value;
        return true;
    }
    return false;
}

}} // namespace Surf::PrefixTree