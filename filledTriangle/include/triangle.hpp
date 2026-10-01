#pragma once

#include "colour.hpp"
#include "image.hpp"
#include "line.hpp"
#include "point.hpp"

class Triangle {
  Point p0;
  Point p1;
  Point p2;

public:
  Triangle(Point a, Point b, Point c) : p0(a), p1(b), p2(c) {}

  const Point &a() const { return p0; }
  const Point &b() const { return p1; }
  const Point &c() const { return p2; }

  void draw(Image &image, Colour color) const {
    Line(p0, p1).draw(image, color);
    Line(p1, p2).draw(image, color);
    Line(p2, p0).draw(image, color);
  }

  void drawTriangle(Image &image, Colour color) const {
    draw(image, color);
  }

  void drawFilledTriangle(Image &image, Colour color) const {
  }
};
