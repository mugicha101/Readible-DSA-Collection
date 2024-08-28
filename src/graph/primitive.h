#pragma once

#include <stddef.h>
#include <unordered_map>

// T: element type (must be copyable, must have default constructor)
// N: number of children per node
template<class T = int, size_t N = 2>
struct NaryNode {
  NaryNode() {}
  NaryNode(T val) : val(val) {}

  T &operator*() const { return val; }
  const NaryNode<T, N> *operator[](size_t index) const { return next[index]; }
  NaryNode<T, N> *operator[](size_t index) { return next[index]; }
  NaryNode<T, N> *left() const { return next[0]; }
  NaryNode<T, N> *right() const { return next[N-1]; }
private:
  T val;
  NaryNode<T, N> *next[N] = {};
};

template<class T>
using BinaryTree = NaryTree<T, 2>;

// K: key type (must be hashable)
// V: value type
template<class K, class V>
struct HashNode {
  HashNode() {}

private:
  std::unordered_map<K, HashNode *> next;
};
