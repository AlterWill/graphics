#pragma once

#include <cstdint>

class Colour {
    uint32_t color = 0;

public:
    Colour() = default;

    Colour(uint8_t red, uint8_t green, uint8_t blue)
    {
        color = red |
                (static_cast<uint32_t>(green) << 8) |
                (static_cast<uint32_t>(blue) << 16) |
                (255u << 24);
    }

    uint32_t getColor() const
    {
        return color;
    }
};
