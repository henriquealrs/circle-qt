#include "circle.h"
#include <math.h>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

Circle::~Circle()
{
    cout << "Circle destructor" << endl;
}

std::vector<vec2d> Circle::get_points(uint32_t n) const
{
    n = (int) (this->_r * 2 * M_PI);
    vector<vec2d> ret;
    ret.reserve(n);

    double fn = static_cast<float>(n);
    double angle_step = 2 * M_PI / fn;

    double angle = 0.0;
    for(int i = 0; i < n; ++i) {
        double fdx = (double)_r * cos(angle);
        double fdy = (double)_r * sin(angle);

        ret.push_back(
                    vec2d(this->_c.x + (int)fdx, this->_c.y + int(fdy))
                    );
        angle += angle_step;
    }
    return ret;
}
