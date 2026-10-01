#pragma once

#include "colour.hpp"
#include "image.hpp"
#include "point.hpp"
#include "readFile.hpp"
#include <cmath>
#include <iostream>
#include <set>

class Frame {
  static constexpr Point A{100, 110, 0};
  static constexpr Point B{250, 400, 0};
  static constexpr Point C{400, 300, 0};
  std::vector<std::string> object;
  inline static const std::filesystem::path filePath =
      "/home/alterwill/Github/graphics/objectToRender/diablo3_pose.obj";
  std::vector<Point> points;
  std::set<std::pair<Point, Point>> lines;

  // y = mx + c
  // m = y1 - y2/ x1 - x2
  void drawLine(Image &image, Point A, Point B, Colour color) {
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
        image.setPixel(y, x, color); // Transpose back
      } else {
        image.setPixel(x, y, color);
      }
    }
  }

  void readObjectFile(std::filesystem::path fp, int width, int height) {
    ReadFile objectFile(fp);
    object = objectFile.readByLine();
    for (auto line : object) {
      std::istringstream iss(line);
      std::string prefix;

      if (iss >> prefix) {
        if (prefix == "v") {
          float x, y, z;
          iss >> x >> y >> z;
          int screenX = static_cast<int>((x + 1.0f) * 0.5f * width);
          int screenY = static_cast<int>((1.0f - y) * 0.5f * height);
          points.emplace_back(screenX, screenY, z);
        }
        if (prefix == "f") {
          std::string token;
          std::vector<int> triangleLines;
          triangleLines.reserve(3);

          // 1. Extract each face vertex token (e.g., "1/2/3", "4/5/6")
          while (iss >> token) {
            std::istringstream tokenStream(token);
            std::string vertexStr;

            // 2. Read only the first section up to the first '/'
            if (std::getline(tokenStream, vertexStr, '/')) {
              if (!vertexStr.empty()) {
                // Now vertexStr contains strictly digits like "1", "4", etc.
                int vIndex = std::stoi(vertexStr);
                vIndex--;
                triangleLines.push_back(vIndex);
              }
            }
          }

          if (triangleLines.size() >= 3) {
            Point p0 = points[triangleLines[0]];
            Point p1 = points[triangleLines[1]];
            Point p2 = points[triangleLines[2]];

            lines.insert({p0, p1});
            lines.insert({p1, p2});
            lines.insert({p2, p0});
          }
        }
      }
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

    readObjectFile(filePath, width, height);

    for(auto line : lines){
      drawLine(image, line.first, line.second, Colour(255,0,0));
    }
    /*
    for (auto point : points) {
      std::cout << point.x << ' ' << point.y << ' ' << point.z << std::endl;
    }
    for (auto linePair : lines) {
      std::cout << linePair.first.x << ' ' << linePair.first.y << ' ' << linePair.first.z << " <-> "
                << linePair.second.x << ' ' << linePair.second.y << ' ' << linePair.second.z
                << std::endl;
    }
    */
  }
};
