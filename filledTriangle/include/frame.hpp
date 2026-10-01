#pragma once

#include "colour.hpp"
#include "image.hpp"
#include "line.hpp"
#include "objFile.hpp"
#include "point.hpp"
#include "pointList.hpp"
#include "triangle.hpp"
#include <filesystem>
#include <set>
#include <utility>
#include <vector>

// Builder that collects draw commands and replays them into an Image when
// render() is called.
class Frame {
  std::vector<std::pair<Line, Colour>> lines;
  std::vector<std::pair<Triangle, Colour>> triangles;

public:
  Frame &addLine(Point a, Point b, Colour color) {
    lines.emplace_back(Line(a, b), color);
    return *this;
  }

  Frame &addTriangle(Point a, Point b, Point c, Colour color) {
    triangles.emplace_back(Triangle(a, b, c), color);
    return *this;
  }

  Frame &addFilledTriangle(Point a, Point b, Point c, Colour color) {
    triangles.emplace_back(Triangle(a, b, c), color);
    return *this;
  }

  Frame &addModel(std::filesystem::path fp, int width, int height, Colour color) {
    ObjFile obj;
    obj.load(fp, width, height);

    // Shared edges are drawn once, so the edges are collected in a set first.
    std::set<std::pair<Point, Point>> edges;
    for (const auto &tri : obj.getTriangles()) {
      edges.insert({tri.a(), tri.b()});
      edges.insert({tri.b(), tri.c()});
      edges.insert({tri.c(), tri.a()});
    }
    for (const auto &edge : edges) {
      addLine(edge.first, edge.second, color);
    }
    return *this;
  }

  void render(Image &image) const {
    for (const auto &line : lines) {
      line.first.draw(image, line.second);
    }
    for (const auto &tri : triangles) {
      tri.first.draw(image, tri.second);
    }
  }

  void clear() {
    lines.clear();
    triangles.clear();
  }

  bool empty() const { return lines.empty() && triangles.empty(); }
};