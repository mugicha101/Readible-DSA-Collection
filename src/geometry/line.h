#pragma once

#include "vec.h"

// predefine all shapes so that intersection can use classnames
template<class T, dim_t D> struct Circ;
template<class T, dim_t D> struct Rect;
template<class T> struct Poly;

// stores resulting intersection point(s)
template<class T, dim_t D>
struct LineIntersectRes {
  enum Type { None, OnePoint, Infinite };
  Type type;
  Vec<T, D> point; // only defined if type is OnePoint
};

// Represents a generic line with bounds determined by L
// Represented by L(t) = origin + dir * t
// T: numerical type (int, float, etc.)
// D: number of dimensions (D >= 1)
// L: line type
enum LineType { LineT, RayT, SegT };
template<class T, dim_t D, LineType L>
struct GenLine {
  static_assert(D >= 1);

  LineType type;
  Vec<T, D> origin; // L(0) aka origin of the line
  Vec<T, D> dir; // L'(t) aka direction and magnitude of line

  // constructors
  GenLine(Vec<T, D> origin, Vec<T, D> dir, LineType type = LineType::LineT) : origin(origin), dir(dir), type(type) {}
  GenLine() {}
  template<class... Args>
  GenLine(Args... comps) {
    static_assert(sizeof...(comps) == D * 2);
    auto args = std::initializer_list<std::common_type_t<Args...>>{comps...};
    for (size_t i = 0; i < D; ++i) {
      origin[i] = args[i];
      dir[i] = args[i + D];
    }
  };

  // gets point on line L(t) = origin + dir * t
  constexpr operator()(T t) const {
    return origin + dir * t;
  }

  // constructs line from 2 pts on line (a is origin, b - a is dir)
  constexpr static GenLine<T, D, L> from_pts(Vec<T, D> a, Vec<T, D> b) {
    return { a, b - a };
  }

  // point distance to line
  constexpr T dist(const Vec<T, D> &p);
  constexpr T dist(Vec<T, D> &&p) { dist(p); }

  // line intersection
  template<LineType L2>
  constexpr LineIntersectRes<T, D> intersection(const GenLine<T, D, L2> &) const;
  template<LineType L2>
  constexpr LineIntersectRes<T, D> intersection(GenLine<T, D, L2> &&other) const {
    return intersection(other);
  }

  // shape intersection
  constexpr bool intersects(const Circ<T, D> &) const;
  constexpr bool intersects(Circ<T, D> &&other) const { return intersects(other); }
  constexpr bool intersects(const Rect<T, D> &) const;
  constexpr bool intersects(Rect<T, D> &&other) const { return intersects(other); }
  constexpr bool intersects(const Poly<T> &) const;
  constexpr bool intersects(Poly<T> &&other) const { return intersects(other); }

  // accessors for a and b (endpoints of line)
  // can update one without changing the other
  constexpr Vec<T, D> a() const {
    static_assert(L != LineType::LineT);
    return origin;
  }

  constexpr Vec<T, D> b() const {
    static_assert(L == LineType::SegT);
    return origin + dir;
  }

  constexpr void set_a(const Vec<T, D> &val) {
    static_assert(L != LineType::LineT);
    Vec<T, D> vb = b();
    origin = val;
    dir = vb - origin;
  }
  constexpr Vec<T, D> &set_a(Vec<T, D> &&val) { set_a(val); }

  constexpr void set_b(const Vec<T, D> &val) {
    static_assert(L == LineType::SegT);
    dir = val - origin;
  }
  constexpr void set_b(Vec<T, D> &&val) { set_b(val); }
};

// shorthands
template<class T, dim_t D>
using Line = GenLine<T, D, LineType::LineT>;
template<class T>
using Line2 = Line<T, 2>;
template<class T>
using Line3 = Line<T, 3>;
using Line2i = Line2<int>;
using Line2f = Line2<float>;
using Line2d = Line2<double>;
using Line3i = Line3<int>;
using Line3f = Line3<float>;
using Line3d = Line3<double>;

template<class T, dim_t D>
using Ray = GenLine<T, D, LineType::RayT>;
template<class T>
using Ray2 = Ray<T, 2>;
template<class T>
using Ray3 = Ray<T, 3>;
using Ray2i = Ray2<int>;
using Ray2f = Ray2<float>;
using Ray2d = Ray2<double>;
using Ray3i = Ray3<int>;
using Ray3f = Ray3<float>;
using Ray3d = Ray3<double>;

template<class T, dim_t D>
using Seg = GenLine<T, D, LineType::SegT>;
template<class T>
using Seg2 = Seg<T, 2>;
template<class T>
using Seg3 = Seg<T, 3>;
using Seg2i = Seg2<int>;
using Seg2f = Seg2<float>;
using Seg2d = Seg2<double>;
using Seg3i = Seg3<int>;
using Seg3f = Seg3<float>;
using Seg3d = Seg3<double>;
