#include "Sphere.hpp"

namespace rt
{
    bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
    {
        Vec3 oc = r.orig - center;
        double a = r.dir.lenght_sq();
        double half_b = dot(oc, r.dir);
        double c = oc.lenght_sq() - radius * radius;
        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0)
            return false;

        double sqrtd = sqrt(discriminant);

        double root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        Vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
}