#pragma once

#include "Ray.hpp"

namespace rt
{
    struct HitRecord
    {
        Point3 p;
        Vec3 normal;
        double t;
        bool front_face;

        inline void set_face_normal(const Ray &r, const Vec3 &outward_normal)
        {
            front_face = dot(r.dir, outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };

    class Hittable
    {
    public:
        virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &hit) const = 0;
    };
}