#pragma once

#include "iterator.h"
#include <stddef.h>
#include <cstring>
#include <cmath>

// Vec - represents an mathematical vector

// T: numerical type (int, float, etc.)
// D: number of dimensions (D >= 1)
template <class T, size_t D>
class Vec {
  static_assert(D >= 1);

  T p[D];
  
  using Iterator = ArrayIterator<T>;
public:
  // constructors
  template<class... Args>
  Vec(Args... comps) {
    static_assert(sizeof...(comps) == D);
    size_t i = 0;
    for (T c : std::initializer_list<std::common_type_t<Args...>>{comps...}) {
      p[i++] = c;
    }
  };
  Vec() {
    for (size_t i = 0; i < D; ++i) {
      p[i] = T{0};
    }
  }
  Vec(const Vec<T, D> &other) {
    *this = other;
  }
  Vec(Vec<T, D> &&other) {
    *this = std::move(other);
  }

  // assignment
  Vec &operator=(const Vec<T, D> &other) {
    memcpy(p, other.p, sizeof(p));
    return *this;
  }
  Vec &operator=(Vec<T, D> &&other) {
    memmove(p, other.p, sizeof(p));
    return *this;
  }

  // index access (first 4: xyzw, w for barycentric coords)
  const T &operator[](size_t index) const {
    return p[index];
  }
  T &operator[](size_t index) {
    return p[index];
  }
  T x() const {
    return p[0];
  }
  T y() const {
    static_assert(D >= 2);
    return p[1];
  }
  T z() const {
    static_assert(D >= 3);
    return p[2];
  }
  T w() const {
    static_assert(D >= 4);
    return p[3];
  }

  // dot product
  constexpr T dot(Vec<T, D> other) const {
    T res = T{0};
    for (size_t i = 0; i < D; ++i) {
      res += p[i] * other[i];
    }
    return res;
  }

  // magnitude
  constexpr T mag_sqd() const {
    return this->dot(*this);
  }
  T mag() const {
    return std::sqrt(mag_sqd());
  }

  // normal
  Vec<T, D> norm() const {
    return *this / mag();
  }

  // project other onto this
  constexpr Vec<T, D> proj(Vec<T, D> other) const {
    return (this->dot(other) / mag_sqd()) * *this;
  }

  // construct new Vec from components
  template<class... Args>
  Vec<T, sizeof...(Args)> get(Args... fmt) {
    Vec<T, sizeof...(fmt)> res;
    size_t i = 0;
    for (size_t j : std::initializer_list<std::common_type_t<Args...>>{fmt...}) {
      res[i++] = p[j];
    }
    return res;
  }

  Iterator begin() { return Iterator(p); }
  Iterator end() { return Iterator(p + D); }
  size_t size() const { return D; }
};

// operators
template<class T, size_t D>
constexpr Vec<T, D> operator*(Vec<T, D> lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] *= rhs[i];
  }
  return lhs;
}
template<class T, size_t D>
constexpr Vec<T, D> operator*(Vec<T, D> lhs, T rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] *= rhs;
  }
  return lhs;
}
template<class T, size_t D>
constexpr Vec<T, D> operator*(T lhs, Vec<T, D> rhs) {
  return rhs * lhs;
}

template<class T, size_t D>
constexpr Vec<T, D> operator/(Vec<T, D> lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] /= rhs[i];
  }
  return lhs;
}
template<class T, size_t D>
constexpr Vec<T, D> operator/(Vec<T, D> lhs, T rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] /= rhs;
  }
  return lhs;
}

template<class T, size_t D>
constexpr Vec<T, D> operator+(Vec<T, D> lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] += rhs[i];
  }
  return lhs;
}

template<class T, size_t D>
constexpr Vec<T, D> operator-(Vec<T, D> v) {
  for (size_t i = 0; i < D; ++i) {
    v[i] = -v[i];
  }
  return v;
}
template<class T, size_t D>
constexpr Vec<T, D> operator-(Vec<T, D> lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] -= rhs[i];
  }
  return lhs;
}

template<class T, size_t D>
constexpr Vec<T, D> &operator*=(Vec<T, D> &lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] *= rhs[i];
  }
  return lhs;
}
template<class T, size_t D>
constexpr Vec<T, D> &operator*=(Vec<T, D> &lhs, T rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] *= rhs;
  }
  return lhs;
}

template<class T, size_t D>
constexpr Vec<T, D> &operator/=(Vec<T, D> &lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] /= rhs[i];
  }
  return lhs;
}
template<class T, size_t D>
constexpr Vec<T, D> &operator/=(Vec<T, D> &lhs, T rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] /= rhs;
  }
  return lhs;
}

template<class T, size_t D>
constexpr Vec<T, D> &operator+=(Vec<T, D> &lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] += rhs[i];
  }
  return lhs;
}
template<class T, size_t D>
constexpr Vec<T, D> &operator+=(Vec<T, D> &lhs, T rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] += rhs;
  }
  return lhs;
}

template<class T, size_t D>
constexpr Vec<T, D> &operator-=(Vec<T, D> &lhs, Vec<T, D> rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] -= rhs[i];
  }
  return lhs;
}
template<class T, size_t D>
constexpr Vec<T, D> &operator-=(Vec<T, D> &lhs, T rhs) {
  for (size_t i = 0; i < D; ++i) {
    lhs[i] -= rhs;
  }
  return lhs;
}

// shorthands
using Vec2i = Vec<int, 2>;
using Vec2f = Vec<float, 2>;
using Vec2d = Vec<double, 2>;
using Vec3i = Vec<int, 3>;
using Vec3f = Vec<float, 3>;
using Vec3d = Vec<double, 3>;
using Vec4i = Vec<int, 4>;
using Vec4f = Vec<float, 4>;
using Vec4d = Vec<double, 4>;
