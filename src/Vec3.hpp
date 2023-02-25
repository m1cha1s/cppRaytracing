#pragma once

#include <cmath>
#include <iostream>

// extern "C"
// {
// #include <raylib.h>
// }

namespace rt
{
    using std::sqrt;

    class Vec3
    {
    public:
        Vec3();
        Vec3(double x, double y, double z);

        Vec3 operator-() const;
        double operator[](size_t i) const;
        double &operator[](size_t i);

        Vec3 &operator+=(const Vec3 &v);
        Vec3 &operator-=(const Vec3 &v);
        Vec3 &operator*=(const Vec3 &v);
        Vec3 &operator/=(const Vec3 &v);

        Vec3 &operator*=(const double t);
        Vec3 &operator/=(const double t);

        double lenght_sq() const;
        double lenght() const;

        double x, y, z;
    };

    using Point3 = Vec3;
    using Color = Vec3;

    // Utility functions
    std::ostream &operator<<(std::ostream &out, const Vec3 &v);
    Vec3 operator+(const Vec3 &u, const Vec3 &v);
    Vec3 operator-(const Vec3 &u, const Vec3 &v);
    Vec3 operator*(const Vec3 &u, const Vec3 &v);
    Vec3 operator*(double t, const Vec3 &v);
    Vec3 operator*(const Vec3 &u, double t);
    Vec3 operator/(const Vec3 &u, double t);
    double dot(const Vec3 &u, const Vec3 &v);
    Vec3 cross(const Vec3 &u, const Vec3 &v);
    Vec3 unit_vector(Vec3 u);
}