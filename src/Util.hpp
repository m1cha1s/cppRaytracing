#pragma once

#include <cstdlib>
#include "Ray.hpp"

extern "C"
{
#include <raylib.h>
}

inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}
Vector4 to_vector4(const rt::Vec3 &v, double t)
{
    return (Vector4){float(v.x), float(v.y), float(v.z), float(t)};
}