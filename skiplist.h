#pragma once

#include "iterator.h"
#include <stddef.h>
#include <random>
#include <cmath>

// T: element type (must implement comparisons and be copyable, must have a default constructor)
// L: max levels (L >= 1)
template<class T = int, size_t L = 12>
class SkipList {
  static_assert(L >= 1);

  struct Node {
    Node(size_t layers, T value) : layers(layers), value(value) {}
    Node(size_t layers) : layers(layers) {}
    Node() {}

    T &operator*() { return value; }
    T *operator->() { return &value; }

    T value;
    size_t layers;
    Node *next[L] = {};
  };

  using Iterator = LinkedListIterator<T, Node>;
public:
  // p: probability that element in layer k is in layer k+1 (0 <= P <= 1)
  SkipList(double p = 0.5) : head(0), tail(L), gd(p) {
    for (size_t i = 0; i < L; ++i)
      head.next[i] = &tail;
  }
  ~SkipList() {
    clear();
  }

  Iterator begin() { return Iterator(head.next[0]); }
  Iterator end() { return Iterator(&tail); }
  size_t size() const { return n; }

  // gets first instance of value
  // returns nullptr if none exist
  T *find(const T &value) const {
    Node *node = search(value);
    return node == tail ? nullptr : &node->val;
  }
  T *find(T value) const { return find(value); }
  T *find(T &&value) const { return find(value); }

  // insert one instance of this value
  void insert(T value) {
    Node *prev = search_prev(value);
    Node *node = new Node(sample_layers(), value);
    for (size_t i = 0; i < node->layers; ++i) {
      node->next[i] = prev->next[i];
      prev->next[i] = node;
    }
    ++n;
  }

  // insert value if not in skiplist
  // return true if insertion performed
  bool insert_if_none(T value) {
    Node *prev = search_prev(value);
    if (prev->next[0] != &tail && prev->next[0]->value == value)
      return false;

    Node *node = new Node(sample_layers());
    for (size_t i = 0; i < node->layers; ++i) {
      node->next[i] = prev->next[i];
      prev->next[i] = node;
    }
    return true;
  }

  // remove one instance of this value
  // return true if removal performed
  bool erase(T value) {
    Node *prev = search_prev(value);
    Node *node = prev->next[0];
    if (node == &tail || node->value != value)
      return false;
    
    for (size_t i = 0; i < node->layers; ++i)
      prev->next[i] = node->next[i];
    delete node;
    --n;
    return true;
  }

  // clears list
  void clear() {
    Node *curr = head.next[0];
    while (curr != &tail) {
      Node *next = curr->next[0];
      delete curr;
      curr = next;
    }
    for (size_t i = 0; i < L; ++i)
      head.next[i] = &tail;
    n = 0;
  }
private:
  size_t n = 0;

  Node head;
  Node tail;

  std::default_random_engine rng;
  std::geometric_distribution<size_t> gd;

  // finds last node with value less than target
  Node *search_prev(const T &target) {
    size_t layer = L - 1;
    Node *curr = &head;
    while (true) {
      if (curr->next[layer] == &tail || curr->next[layer]->value >= target) {
        if (layer-- == 0) break;
      } else
        curr = curr->next[layer];
    }
    return curr;
  };

  // finds first node with value at least target
  Node *search(const T &target) {
    return prev(target)->next[0];
  }

  size_t sample_layers() {
    return std::max(gd(rng) + 1, L);
  };
};