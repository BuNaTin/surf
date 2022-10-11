#pragma once

#include <surfTypes.h>
#include <types.h>

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace Surf { inline namespace PrefixTree {

class Tree {
public:
    Tree() { m_head = new Node('\0'); }
    ~Tree() { delete m_head; }

    bool insert(const std::string &str, const u64 shift) {
        Node *cur_node = m_head;
        for (auto symb : str) {
            if (!cur_node->hasChild()) {
                cur_node->data = std::vector<Node *>();
            }
            if (cur_node->child(symb) == nullptr) {
                cur_node->data->push_back(new Node(symb));
            }
            cur_node = cur_node->child(symb);
        }
        if (cur_node->hasChild()) {
            if (cur_node->child(SPECIAL_CHAR) == nullptr) {
                cur_node->data->push_back(new Node(SPECIAL_CHAR));
            }
            cur_node = cur_node->child(SPECIAL_CHAR);
        }
        cur_node->value = shift;
        return true;
    }

    bool find(const std::string &str, u64 &value) {
        Node *cur_node = m_head;
        auto it = str.begin(), end = str.end();
        for (; it != end && cur_node != nullptr && cur_node->hasChild(); ++it) {
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

public:
    enum CHILDREN {
        SIZE = 256,
        SPECIAL_CHAR = '$'
    }; // all in bytes
    struct Node {
        /* NEVER CONTAIN CHILDREN AT '\0' */
        std::optional<std::vector<Node *>> data;
        char symb;
        value_t value;

        Node(char s) : symb(s) {}

        bool hasChild() { return !!data; }

        Node *child(char symb) {
            if (!data) {
                std::cerr << "Child [" << symb << "] of nullopt data\n";
                return nullptr;
            }
            auto it = std::find_if(
                    data->begin(), data->end(), [symb](Node *node) {
                        return node->symb == symb;
                    });
            if (it == data->end()) {
                return nullptr;
            }
            return *it;
        }

        ~Node() {
            if (!data) return;
            for (auto &&node : *data)
                delete node;
        }
    };

    Node *m_head;
    u32 cnt = 0;
};

}} // namespace Surf::PrefixTree