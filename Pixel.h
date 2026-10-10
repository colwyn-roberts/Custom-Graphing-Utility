#pragma once
#include <iostream>
class Pixel {
public:
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
    Pixel(uint8_t r, uint8_t g, uint8_t b) {
        red = r;
        green = g;
        blue = b;
    }
    Pixel() {
        red = 0;
        green = 0;
        blue = 0;
    }
};