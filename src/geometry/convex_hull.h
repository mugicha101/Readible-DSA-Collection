#pragma once

#include "vec.h"
#include <algorithm>

// static class for doing convex hull operations
template<class T, dim_t D>
struct ConvexHull {
  // returns CCW convex hull
  static std::vector<Vec<T, D>> calc(std::vector<Vec<T, D>> &&pts) {
    static_assert(D >= 2);
    if constexpr (std::is_same_v<D, 2>) {
      // 2D convex hull
      convex_hull_2d(pts);
    } else {
      // ND convex hull
      convex_hull_nd(pts);
    }
    return pts;
  }

  static std::vector<Vec<T, D>> calc(const std::vector<Vec<T, D>> &pts) {
    std::vector<Vec<T, D>> copy = pts;
    return calc(std::move(copy));
  }
private:
  static void convex_hull_2d(std::vector<Vec<T, D>> &pts) {
    std::vector<T> angles;
    angles.reserve(pts.size());
    for (Vec<T, D> &p : pts) {
      angles.push_back(p.angle());
    }
    std::vector<int> order(pts.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int i, int j) {
      return angles[i] < angles[j];
    });

    // TODO
    size_t j = 1;
    for (size_t i = 1; i < pts.size(); ++i) {
      size_t a = pts[j-1];
      size_t b = pts[i];
    }
  }

  static void convex_hull_nd(std::vector<Vec<T, D>> &pts) {
    // TODO
  }
};

// shorthands
template<class T>
using ConvexHull2D = ConvexHull<T, 2>;