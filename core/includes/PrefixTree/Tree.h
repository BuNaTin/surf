#pragma once

#include <string>
#include <types.h>

namespace Surf { inline namespace PrefixTree {

class Tree {
public:
    Tree() { m_head = new Node; }
    ~Tree() { delete m_head; }

    bool insert(const std::string &str, const u64 shift) {
        Node *cur_node = m_head;
        for (auto symb : str) {
            if (cur_node->data[symb] == nullptr) {
                cur_node->data[symb] = new Node;
            }
            cur_node = cur_node->data[symb];
        }
        if(cur_node->hasChild()) {
            if (cur_node->data[SPECIAL_CHAR] == nullptr) {
                cur_node->data[SPECIAL_CHAR] = new Node;
            }
            cur_node = cur_node->data[SPECIAL_CHAR];
        }
        cur_node->set(shift);
        return true;
    }

    bool find(const std::string &str, u64 &value) {
        Node *cur_node = m_head;
        auto it = str.begin(), end = str.end();
        for (; it != end && cur_node != nullptr; ++it) {
            std::cout << "GO : " << *it << '\n';
            cur_node = cur_node->data[*it];
        }
        if (cur_node != nullptr && cur_node->data[SPECIAL_CHAR] != nullptr) {
            cur_node = cur_node->data[SPECIAL_CHAR];
        }
        if (it == end && cur_node != nullptr) {
            if (cur_node->data[VALUE] != nullptr) {
                value = cur_node->value();
                return true;
            }
        }
        return false;
    }

public:
    enum TYPE { VALUE, CHILDREN = 1 };
    enum CHILDREN {
        SIZE = 256,
        BYTES = 8,
        TOTAL = 2048,
        VALUE = 0,
        SPECIAL_CHAR = '$'
    }; // all in bytes
    struct Node {
        /* NEVER CONTAIN CHILDREN AT '\0' */
        Node *data[CHILDREN::SIZE];
        Node() {
            std::fill(data, data + CHILDREN::SIZE, nullptr);
        }
        bool hasChild() {
            if (reinterpret_cast<u64>(data[0]) != 0) {
                return false;
            }
            for (Node **i = data + 1, **end = data + CHILDREN::SIZE;
                 i != end;
                 ++i) {
                if (*i != nullptr) {
                    return true;
                }
            }
            return false;
        }
        void set(const u64 value) {
            data[VALUE] = reinterpret_cast<Node *>(value);
        }
        u64 value() { return reinterpret_cast<u64>(data[VALUE]); }
        ~Node() {
            for (Node **i = data + 1, **end = data + CHILDREN::SIZE;
                 i != end;
                 ++i) {
                delete *i;
            }
        }
    };

    Node *m_head;
    u32 cnt = 0;
};

}} // namespace Surf::PrefixTree