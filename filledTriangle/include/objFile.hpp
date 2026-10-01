#pragma once

#include "pointList.hpp"
#include "readFile.hpp"
#include "triangle.hpp"
#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

// Parses a Wavefront .obj file into a point list plus the triangles it
// references. Only the `v` and `f` directives are understood.
class ObjFile {
  PointList points;
  std::vector<Triangle> triangles;

  void readVertex(std::istringstream &iss, int width, int height) {
    float x, y, z;
    iss >> x >> y >> z;
    int screenX = static_cast<int>((x + 1.0f) * 0.5f * width);
    int screenY = static_cast<int>((1.0f - y) * 0.5f * height);
    points.add(static_cast<float>(screenX), static_cast<float>(screenY), z);
  }

  void readFace(std::istringstream &iss) {
    std::string token;
    std::vector<int> triangleLines;
    triangleLines.reserve(3);

    while (iss >> token) {
      std::istringstream tokenStream(token);
      std::string vertexStr;
      if (std::getline(tokenStream, vertexStr, '/')) {
        if (!vertexStr.empty()) {
          triangleLines.push_back(std::stoi(vertexStr) - 1);
        }
      }
    }

    if (triangleLines.size() < 3) {
      return;
    }

    triangles.emplace_back(points.at(triangleLines[0]), points.at(triangleLines[1]),
                           points.at(triangleLines[2]));
  }

public:
  void load(std::filesystem::path fp, int width, int height) {
    ReadFile objectFile(fp);
    for (auto line : objectFile.readByLine()) {
      std::istringstream iss(line);
      std::string prefix;
      if (!(iss >> prefix)) {
        continue;
      }
      if (prefix == "v") {
        readVertex(iss, width, height);
      } else if (prefix == "f") {
        readFace(iss);
      }
    }
  }

  const PointList &getPoints() const { return points; }

  const std::vector<Triangle> &getTriangles() const { return triangles; }
};
