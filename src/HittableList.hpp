#pragma once

#include "Hittable.hpp"

#include <vector>

namespace rt
{

    class HittableList : public Hittable
    {
    public:
        HittableList() {}
        HittableList(Hittable *object) { add(object); }
        ~HittableList() { clear(); }

        void clear()
        {
            for (int i = 0; i < objects.size(); i++)
            {
                delete objects[i];
                objects[i] = nullptr;
            }
            objects.clear();
        }

        void add(Hittable *object)
        {
            objects.push_back(object);
        }
        virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    private:
        std::vector<Hittable *> objects;
    };

}