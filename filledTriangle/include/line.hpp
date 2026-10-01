#pragma once

#include "colour.hpp"
#include "image.hpp"
#include "point.hpp"
#include <cmath>

class Line {
  Point a;
  Point b;

public:
  Line(Point start, Point end) : a(start), b(end) {}

  void draw(Image &image, Colour color) const {
    Point A = a;
    Point B = b;

    bool steep = std::abs(B.y - A.y) > std::abs(B.x - A.x);
    if (steep) {
      std::swap(A.x, A.y);
      std::swap(B.x, B.y);
    }
    if (A.x > B.x) {
      std::swap(A.x, B.x);
      std::swap(A.y, B.y);
      std::swap(A.z, B.z);
    }

    int dx = B.x - A.x;
    int dy = B.y - A.y;
    if (dx == 0) {
      if (steep) {
        image.setPixel(A.y, A.x, color);
      } else {
        image.setPixel(A.x, A.y, color);
      }
      return;
    }

    float slope = static_cast<float>(dy) / dx;
    for (int x = A.x; x <= B.x; x++) {
      int y = std::round(A.y + (x - A.x) * slope);
      if (steep) {
        image.setPixel(y, x, color);
      } else {
        image.setPixel(x, y, color);
      }
    }
  }
};