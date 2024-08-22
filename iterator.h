#pragma once

#include <iterator>

// Iterator templates to improve the readibility of collections
// T: element type
// P: pointer class (has * and -> overloaded like a pointer)
template<class T, class P>
struct LinkedListIterator {
  using iterator_category = std::forward_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T&;
  LinkedListIterator(P *ptr) : ptr(ptr) {}

  reference operator*() { return **ptr; }
  pointer operator->() { return *ptr; }
  bool operator==(const LinkedListIterator<T, P> &other) const { return ptr == other.ptr; }
  bool operator!=(const LinkedListIterator<T, P> &other) const { return ptr != other.ptr; }
  
  LinkedListIterator<T, P> &operator++() {
    ptr = ptr->next[0];
    return *this;
  }

  LinkedListIterator<T, P> &operator++(int) {
    ptr = ptr->next[0];
    return *this;
  }
private:
  P *ptr;
};