#pragma once

typedef struct Point {
  float x{}, y{}, z{};

  bool operator<(const Point &o) const {
    if (x != o.x) {
      return x < o.x;
    }
    if (y != o.y) {
      return y < o.y;
    }
    return z < o.z;
  }
  bool operator==(const Point &) const = default;
} Point;
