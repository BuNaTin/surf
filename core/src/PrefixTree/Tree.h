#pragma once

#include <surfTypes.h>
#include <types.h>
#include <PrefixTree/Node.h>

namespace Surf { inline namespace PrefixTree {

struct Node;

class Tree {
public:
    Tree() { m_head = new Node; }
    ~Tree() { delete m_head; }

    bool insert(const key_t &key, const value_t value);
    bool find(const key_t &key, u64 &value);

    Node* head() { return m_head; }

    u64 size() { return m_size; }

public:
    enum CHILDREN { SPECIAL_CHAR = '$' }; // all in bytes

private:
    Node *m_head;
    u64 m_size = 0;
};

}} // namespace Surf::PrefixTree