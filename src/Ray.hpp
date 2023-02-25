#pragma once

#include "Vec3.hpp"

namespace rt
{
    class Ray
    {
    public:
        Ray() {}
        Ray(const Point3 &origin, const Vec3 &direction)
        {
            orig = origin;
            dir = direction;
        }

        Point3 at(double t) const
        {
            return orig + t * dir;
        }

        Point3 orig;
        Vec3 dir;
    };
}