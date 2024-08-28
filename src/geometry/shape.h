

#pragma once

#include "line.h"
#include "convex_hull.h"
#include <iterator>
#include <vector>
#include <utility>

// General template args:
// T: numerical type (int, float, etc.)
// D: number of dimensions (D >= 1)

// Represents a circle in D dimensions
template<class T, dim_t D>
struct Circ {
  static_assert(D >= 1);

  Vec<T, D> pos;
  T radius;

  // returns distance from point to nearest edge (negative if overlapping)
  constexpr T dist(const Vec<T, D> &p);
  constexpr T dist(Vec<T, D> &&p) { dist(p); }

  // line intersection
  template<LineType L> constexpr bool intersects(const GenLine<T, D, L> &) const;
  template<LineType L> constexpr bool intersects(GenLine<T, D, L> &&other) const { return intersects(other); }

  // shape intersection
  constexpr bool intersects(const Circ<T, D> &) const;
  constexpr bool intersects(Circ<T, D> &&other) const { return intersects(other); }
  constexpr bool intersects(const Rect<T, D> &) const;
  constexpr bool intersects(Rect<T, D> &&other) const { return intersects(other); }
  constexpr bool intersects(const Poly<T> &) const;
  constexpr bool intersects(Poly<T> &&other) const { return intersects(other); }
};

// Represents a rectangle in D dimensions
template<class T, dim_t D>
struct Rect {
  static_assert(D >= 1);

  Vec<T, D> pos; // position of corner where all components are minimized (ex: bottom-left for 2D)
  Vec<T, D> size;

  // convert to poly
  Poly<T> to_poly() {
    static_assert(D == 2);
    // TODO
  }

  // shape intersection
};

// Represents a convex 2D polygon
template<class T>
class Poly {
  const std::vector<Vec2<T>> pts; // points (CCW)
public:
  // constructs a poly by finding the convex hull of the points
  // pts do not need to be ordered
  Poly(const std::vector<Vec2<T>> &pts) : pts(ConvexHull<T, 2>::calc(pts)) {}

  std::vector<Vec2<T>>::iterator begin() { return pts.begin(); }
  std::vector<Vec2<T>>::iterator end() { return pts.end(); }
  size_t size() const { return pts.size(); }
};

// shorthands
template<class T>
using Circ2 = Circ<T, 2>;
template<class T>
using Circ3 = Circ<T, 3>;
using Circ2i = Circ2<int>;
using Circ2f = Circ2<float>;
using Circ2d = Circ2<double>;
using Circ3i = Circ3<int>;
using Circ3f = Circ3<float>;
using Circ3d = Circ3<double>;

template<class T>
using Rect2 = Rect<T, 2>;
template<class T>
using Rect3 = Rect<T, 3>;
using Rect2i = Rect2<int>;
using Rect2f = Rect2<float>;
using Rect2d = Rect2<double>;
using Rect3i = Rect3<int>;
using Rect3f = Rect3<float>;
using Rect3d = Rect3<double>;
