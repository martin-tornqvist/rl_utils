#include "bresenham.hpp"

#include <cstdlib>

void bresenham(P p, const P& tgt, std::vector<P>& out)
{
    out.clear();

    int delta_x(tgt.x - p.x);

    // If x1 == x2, then it does not matter what we set here
    const char ix = (delta_x > 0) - (delta_x < 0);

    delta_x = std::abs(delta_x) << 1;

    int delta_y = tgt.y - p.y;

    // If y1 == y2, then it does not matter what we set here
    const char iy = (delta_y > 0) - (delta_y < 0);

    delta_y = std::abs(delta_y) << 1;

    out.push_back(p);

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error = delta_y - (delta_x >> 1);

        while (p.x != tgt.x)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                p.y += iy;
            }
            // else do nothing

            error += delta_y;
            p.x += ix;

            out.push_back(p);
        }
    }
    else // delta_x < delta_y
    {
        // error may go below zero
        int error = delta_x - (delta_y >> 1);

        while (p.y != tgt.y)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                p.x += ix;
            }
            // else do nothing

            error += delta_x;
            p.y += iy;

            out.push_back(p);
        }
    }
}
