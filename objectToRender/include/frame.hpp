#pragma once

#include "colour.hpp"
#include "image.hpp"
#include "point.hpp"
#include <cmath>

class Frame {
  static constexpr Point A{100, 110, 0};
  static constexpr Point B{250, 400, 0};
  static constexpr Point C{400, 300, 0};

  // y = mx + c
  // m = y1 - y2/ x1 - x2
  void drawLine(Image &image, Point A, Point B, Colour color) {
    /*
    if(A.x > B.x){
      std::swap(A.x,B.x);
      std::swap(A.y,B.y);
    }
    */
    for (int x = A.x; x <= B.x; x++) {
      float t = (x - A.x) / static_cast<float>(B.x - A.x);
      int y = std::round(A.y + (B.y - A.y) * t);
      image.setPixel(x, y, color);
    }
  }

public:
  Frame(Image &image, int width, int height) {
    image.setPixel(A.x, A.y, Colour(255, 0, 0));
    image.setPixel(B.x, B.y, Colour(0, 255, 0));
    image.setPixel(C.x, C.y, Colour(0, 0, 255));

    drawLine(image, A, B, Colour(255, 0, 0));
    drawLine(image, B, C, Colour(0, 255, 0));
    drawLine(image, A, C, Colour(0, 0, 255));
  }
};
