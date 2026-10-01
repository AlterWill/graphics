#pragma once

#include "point.hpp"
#include <cstddef>
#include <vector>

class PointList {
  std::vector<Point> points;

public:
  void add(const Point &p) { points.push_back(p); }

  void add(float x, float y, float z) { points.emplace_back(x, y, z); }

  std::size_t size() const { return points.size(); }

  bool empty() const { return points.empty(); }

  Point &at(std::size_t index) { return points.at(index); }

  const Point &at(std::size_t index) const { return points.at(index); }

  std::vector<Point>::iterator begin() { return points.begin(); }

  std::vector<Point>::iterator end() { return points.end(); }

  std::vector<Point>::const_iterator begin() const { return points.begin(); }

  std::vector<Point>::const_iterator end() const { return points.end(); }
};