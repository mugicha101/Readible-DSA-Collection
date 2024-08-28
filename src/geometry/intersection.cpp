#include "shape.h"

// Implements intersection calcs for primitives

// static class to implement trivial intersection calculations
template<class T, dim_t D>
struct Intersection {
  // finds intersection point between two lines (ignoring endpoint bounds)
  template<LineType L1, LineType L2>
  static void find_helper(LineIntersectRes<T, D> &res, const GenLine<T, D, L1> &a, const GenLine<T, D, L2> &b) {
    // TODO
    if (a.dir.norm() == b.dir.norm()) {
      // TODO
      return;
    }
  }

  // finds intersection point between two lines (respecting endpoint bounds)
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, LineT> &a, const GenLine<T, D, LineT> &b) {
    find_helper<LineT, LineT>(res, a, b);
  }
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, LineT> &a, const GenLine<T, D, RayT> &b) {
    find_helper<LineT, RayT>(res, a, b);
  }
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, LineT> &a, const GenLine<T, D, SegT> &b) {
    find_helper<LineT, SegT>(res, a, b);
  }
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, RayT> &a, const GenLine<T, D, RayT> &b) {
    find_helper<RayT, RayT>(res, a, b);
  }
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, RayT> &a, const GenLine<T, D, SegT> &b) {
    find_helper<RayT, SegT>(res, a, b);
  }
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, SegT> &a, const GenLine<T, D, SegT> &b) {
    find_helper<SegT, SegT>(res, a, b);
  }

  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, RayT> &a, const GenLine<T, D, LineT> &b) { return insersects(b, a); }
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, SegT> &a, const GenLine<T, D, LineT> &b) { return insersects(b, a); }
  static void find(LineIntersectRes<T, D> &res, const GenLine<T, D, SegT> &a, const GenLine<T, D, RayT> &b) { return insersects(b, a); }

  // return true if intersection exists
  static bool exists(const GenLine<T, D, LineT> &line, const Circ<T, D> &circ);
  static bool exists(const GenLine<T, D, LineT> &line, const Rect<T, D> &rect);
};
