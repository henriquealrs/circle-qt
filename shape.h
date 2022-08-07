#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <stdint.h>

struct vec2d {
    int x;
    int y;
    vec2d() = delete;
    vec2d(int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
public:
    virtual std::vector<vec2d> get_points(uint32_t n) const = 0;
};

#endif // SHAPE_H
