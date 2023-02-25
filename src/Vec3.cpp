#include "Vec3.hpp"

#include "Util.hpp"

namespace rt
{

    Vec3::Vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vec3::Vec3(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3 Vec3::operator-() const
    {
        return Vec3(-x, -y, -z);
    }
    double Vec3::operator[](size_t i) const
    {
        switch (i)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;

        default:
            return 0;
        }
    }
    double &Vec3::operator[](size_t i)
    {
        switch (i)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;

        default:
            return x;
        }
    }

    Vec3 &Vec3::operator+=(const Vec3 &v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }
    Vec3 &Vec3::operator-=(const Vec3 &v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }
    Vec3 &Vec3::operator*=(const Vec3 &v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        return *this;
    }
    Vec3 &Vec3::operator/=(const Vec3 &v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        return *this;
    }

    Vec3 &Vec3::operator*=(const double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    Vec3 &Vec3::operator/=(const double t)
    {
        return *this *= 1 / t;
    }

    double Vec3::lenght_sq() const
    {
        return x * x + y * y + z * z;
    }
    double Vec3::lenght() const
    {
        return sqrt(lenght_sq());
    }

    Vec3 Vec3::random()
    {
        return Vec3(random_double(), random_double(), random_double());
    }

    Vec3 Vec3::random(double min, double max)
    {
        return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    // Utility functions
    std::ostream &
    operator<<(std::ostream &out, const Vec3 &v)
    {
        return out << v.x << ' ' << v.y << ' ' << v.z;
    }

    Vec3 operator+(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
    }

    Vec3 operator-(const Vec3 &u, const Vec3 &v)
    {
        return u + -v;
    }

    Vec3 operator*(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
    }

    Vec3 operator*(double t, const Vec3 &v)
    {
        return Vec3(v.x * t, v.y * t, v.z * t);
    }

    Vec3 operator*(const Vec3 &u, double t)
    {
        return t * u;
    }

    Vec3 operator/(const Vec3 &u, double t)
    {
        return (1 / t) * u;
    }

    double dot(const Vec3 &u, const Vec3 &v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    Vec3 cross(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x);
    }

    Vec3 unit_vector(Vec3 u)
    {
        return u / u.lenght();
    }

    Vec3 random_in_unit_sphere()
    {
        while (true)
        {
            Vec3 p = Vec3::random(-1, 1);
            if (p.lenght_sq() >= 1)
                continue;
            return p;
        }
    }

    Vec3 random_unit_sphere()
    {
        return unit_vector(random_in_unit_sphere());
    }

    Vec3 random_in_hemisphere(const Vec3 &normal)
    {
        Vec3 in_unit_sphere = random_in_unit_sphere();
        if (dot(in_unit_sphere, normal) > 0.0)
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }
}