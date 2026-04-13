#include <cstddef>

template < class T, size_t K >
struct BTree
{
  T val[K];
  BTree< T, K >* childs[K + 1];
  BTree< T, K >* parent;
};

template < class T, size_t K >
struct BTreeIt
{
  size_t s;
  BTree< T, K >* current;
};
template < class T, size_t K >
BTree< T, K >* minimum(BTree< T, K >* root)
{
  if (!root) {
    return root;
  }

  while (root->childs[0]) {
    root = root->childs[0];
  }
  return root;
}

template < class T, size_t K >
BTree< T, K >* maximum(BTree< T, K >* root)
{
  if (!root) {
    return root;
  }

  while (root->childs[K]) {
    root = root->childs[K];
  }
  return root;
}
template < class T, size_t K >
T value(BTreeIt< T, K > it)
{
  return it.current->val[it.s];
}

template < class T, size_t K >
BTreeIt< T, K > next(BTreeIt< T, K > it)
{
  BTree< T, K >* node = it.current;
  size_t s = it.s;

  if (!node) {
    return {0, nullptr};
  }

  if (node->childs[s + 1]) {
    node = node->childs[s + 1];
    node = minimum(node);
    return {0, node};
  }

  if (s + 1 < K && node->val[s + 1]) {
    return {s + 1, node};
  }

  while (node->parent) {
    BTree< T, K >* parent = node->parent;

    for (size_t i = 0; i < K + 1; ++i) {
      if (parent->childs[i] == node) {
        if (i < K && parent->val[i]) {
          return {i, parent};
        }
        node = parent;
        break;
      }
    }
  }

  return {0, nullptr};
}

template < class T, size_t K >
BTreeIt< T, K > prev(BTreeIt< T, K > it)
{
  BTree< T, K >* node = it.current;
  size_t s = it.s;

  if (!node) {
    return {0, nullptr};
  }

  if (node->childs[s]) {
    node = node->childs[s];
    node = maximum(node);
    return {K - 1, node};
  }

  if (s > 0) {
    return {s - 1, node};
  }

  while (node->parent) {
    BTree< T, K >* parent = node->parent;

    for (size_t i = 0; i < K + 1; ++i) {
      if (parent->childs[i] == node) {
        if (i > 0) {
          return {i - 1, parent};
        }
        node = parent;
        break;
      }
    }
  }

  return {0, nullptr};
}

template < class T, size_t K >
bool hasNext(BTreeIt< T, K > it)
{
  return next(it).current != nullptr;
}

template < class T, size_t K >
bool hasPrev(BTreeIt< T, K > it)
{
  return prev(it).current != nullptr;
}



