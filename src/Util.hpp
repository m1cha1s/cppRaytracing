#pragma once

#include <cstdlib>
#include "Ray.hpp"

extern "C"
{
#include <raylib.h>
}

double random_double();
double random_double(double min, double max);
double clamp(double x, double min, double max);
Vector4 to_vector4(const rt::Vec3 &v, double t);