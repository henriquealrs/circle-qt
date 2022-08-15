#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
private:
    vec2d _c;
    int _r;
public:
    Circle() = delete;
    Circle(vec2d& center, int radius) : _c(center), _r(radius) {}
    ~Circle();
    // Shape interface
public:
    std::vector<vec2d> get_points(uint32_t n) const;
};

#endif // CIRCLE_H
