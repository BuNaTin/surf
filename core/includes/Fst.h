#pragma once

#include <vector>

#include <surfTypes.h>

namespace Surf {

inline namespace Louds {
class Dense;
class Sparse;
} // namespace Louds

class Fst {
public:
    value_t *exactKeySearch(const key_t &key);

    Fst(const std::vector<std::pair<key_t, value_t>> &data);
    ~Fst();

    // data
private:
    Louds::Dense *m_dense;
    Louds::Sparse *m_sparse;
};

} // namespace Surf