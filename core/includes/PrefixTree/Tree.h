#pragma once

#include <surfTypes.h>
#include <types.h>

#include <array>
#include <iostream>
#include <optional>
#include <string>

namespace Surf { inline namespace PrefixTree {

class Tree {
public:
    Tree() { m_head = new Node; }
    ~Tree() { delete m_head; }

    bool insert(const key_t &str, const value_t value) {
        Node *cur_node = m_head;
        for (auto symb : str) {
            std::cout << "Insert " << symb << '\n';
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

    bool find(const std::string &str, u64 &value) {
        Node *cur_node = m_head;
        auto it = str.begin(), end = str.end();
        for (; it != end && cur_node != nullptr; ++it) {
            std::cout << "GO : " << *it << '\n';
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

    u64 size() { return m_size; }

public:
    enum TYPE { VALUE, CHILDREN = 1 };
    enum CHILDREN { SIZE = 256, SPECIAL_CHAR = '$' }; // all in bytes
    struct Node {
        /* NEVER CONTAIN CHILDREN AT '\0' */
        std::optional<std::array<Node *, SIZE>> data;
        value_t value;

        Node() {}

        bool hasChild() { return !!data; }

        Node *child(u8 symb) {
            if (!data) {
                std::cerr << "Child [" << symb << "] of nullopt data\n";
                return nullptr;
            }
            return (*data)[symb];
        }

        ~Node() {
            if (!data) return;
            for (auto &&node : *data)
                delete node;
        }
    };

    Node *m_head;
    u64 m_size = 0;
};

}} // namespace Surf::PrefixTree