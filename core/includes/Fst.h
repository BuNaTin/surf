#pragma once

#include <vector>

#include <surfTypes.h>

namespace Surf {

// pre-definition
inline namespace PrefixTree {
struct Node;
}

inline namespace Louds {
class Dense;
class Sparse;
} // namespace Louds

class Fst {
public:
    value_t *exactKeySearch(const key_t &key);

    Fst(const std::vector<std::pair<key_t, value_t>> &data);
    ~Fst();

private:
    void insertToDense(PrefixTree::Node *node, u64 lvl, u64 cur_lvl = 0);

    // data
private:
    Louds::Dense *m_dense;
    // Louds::Sparse *m_sparse;
};

} // namespace Surf