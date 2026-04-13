#include <cstddef>
#include <iostream>
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

int main()
{
  std::cout << "<Tests>\n\n";

  BTree< int, 3 > root;
  root.val[0] = 30;
  root.val[1] = 70;
  root.val[2] = 110;
  root.parent = nullptr;

  for (size_t i = 0; i < 4; ++i) {
    root.childs[i] = nullptr;
  }

  BTree< int, 3 > left;
  left.val[0] = 5;
  left.val[1] = 10;
  left.val[2] = 20;
  left.parent = &root;
  for (size_t i = 0; i < 4; ++i) {
    left.childs[i] = nullptr;
  }

  BTree< int, 3 > mid;
  mid.val[0] = 40;
  mid.val[1] = 50;
  mid.val[2] = 60;
  mid.parent = &root;
  for (size_t i = 0; i < 4; ++i) {
    mid.childs[i] = nullptr;
  }

  BTree< int, 3 > rightMid;
  rightMid.val[0] = 80;
  rightMid.val[1] = 90;
  rightMid.val[2] = 100;
  rightMid.parent = &root;
  for (size_t i = 0; i < 4; ++i) {
    rightMid.childs[i] = nullptr;
  }

  BTree< int, 3 > right;
  right.val[0] = 120;
  right.val[1] = 130;
  right.val[2] = 140;
  right.parent = &root;
  for (size_t i = 0; i < 4; ++i) {
    right.childs[i] = nullptr;
  }

  BTree< int, 3 > c0;
  c0.val[0] = 35;
  c0.val[1] = 38;
  c0.val[2] = 39;
  c0.parent = &mid;

  BTree< int, 3 > c1;
  c1.val[0] = 45;
  c1.val[1] = 48;
  c1.val[2] = 49;
  c1.parent = &mid;

  BTree< int, 3 > c2;
  c2.val[0] = 55;
  c2.val[1] = 58;
  c2.val[2] = 59;
  c2.parent = &mid;

  BTree< int, 3 > c3;
  c3.val[0] = 65;
  c3.val[1] = 68;
  c3.val[2] = 69;
  c3.parent = &mid;

  for (size_t i = 0; i < 4; ++i) {
    c0.childs[i] = nullptr;
    c1.childs[i] = nullptr;
    c2.childs[i] = nullptr;
    c3.childs[i] = nullptr;
  }

  mid.childs[0] = &c0;
  mid.childs[1] = &c1;
  mid.childs[2] = &c2;
  mid.childs[3] = &c3;

  root.childs[0] = &left;
  root.childs[1] = &mid;
  root.childs[2] = &rightMid;
  root.childs[3] = &right;

  int checkData[] = {5,  10, 20, 30, 35, 38, 39, 40, 45,  48,  49,  50,  55, 58,
                     59, 60, 65, 68, 69, 70, 80, 90, 100, 110, 120, 130, 140};

  std::cout << "Tree constructed OK\n";

  BTreeIt< int, 3 > it;
  it.current = minimum(&root);
  it.s = 0;

  const size_t N = 27;

  bool ok = true;

  for (size_t i = 0; i < N; ++i) {
    if (!it.current) {
      std::cout << "stop at i = " << i << "\n";
      ok = false;
      break;
    }

    int v = value(it);

    if (v != checkData[i]) {
      std::cout << "stop at i = " << i << " expd = " << checkData[i] << " got = " << v << "\n";
      ok = false;
    }

    it = next(it);
  }

  if (it.current != nullptr) {
    std::cout << "stop\n";
    ok = false;
  }

  if (ok) {
    std::cout << "NEXT TEST PASSED ✅\n";
  } else {
    std::cout << "NEXT TEST FAILED ❌\n";
  }
}
