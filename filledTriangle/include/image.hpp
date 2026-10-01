#pragma once

#include "colour.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

class Image {
    int width;
    int height;
    std::vector<uint32_t> pixels;

public:
    Image(int width, int height)
        : width(width),
          height(height),
          pixels(static_cast<std::size_t>(width) * static_cast<std::size_t>(height), 0)
    {
    }

    void setPixel(int x, int y, uint32_t color)
    {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return;
        }

        pixels[static_cast<std::size_t>(y) * static_cast<std::size_t>(width) + x] = color;
    }

    void setPixel(int x, int y, Colour color)
    {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return;
        }

        pixels[static_cast<std::size_t>(y) * static_cast<std::size_t>(width) + x] = color.getColor();
    }

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

    const uint32_t* data() const
    {
        return pixels.data();
    }
};
