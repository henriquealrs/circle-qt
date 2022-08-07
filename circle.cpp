#include "circle.h"
#include <math.h>

using std::vector;

std::vector<vec2d> Circle::get_points(uint32_t n) const
{
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
