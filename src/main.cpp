#include <iostream>

#include "Ray.hpp"
#include "Vec3.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Hittable.hpp"

extern "C"
{
#include <raylib.h>
}

rt::Color ray_color(const rt::Ray &r, const rt::Hittable &world)
{
    rt::HitRecord rec;
    if (world.hit(r, 0, INFINITY, rec))
    {
        return 0.5 * (rec.normal + rt::Color(1, 1, 1));
    }
    rt::Vec3 unit_direction = rt::unit_vector(r.dir);
    double t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * rt::Color(1.0, 1.0, 1.0) + t * rt::Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = width / aspect_ratio;

    // World
    rt::HittableList world;
    world.add(new rt::Sphere(rt::Point3(0, 0, -1), 0.5));
    world.add(new rt::Sphere(rt::Point3(0, -100.5, -1), 100));

    // Camera
    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_lenght = 1.0;

    const rt::Point3 origin = rt::Point3(0, 0, 0);
    const rt::Vec3 horizontal = rt::Vec3(viewport_width, 0, 0);
    const rt::Vec3 vertical = rt::Vec3(0, viewport_height, 0);
    const rt::Point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - rt::Vec3(0, 0, focal_lenght);

    InitWindow(width, height, "Raytracing");
    SetTargetFPS(10);

    BeginDrawing();
    {
        ClearBackground(BLACK);
        for (int y = height - 1; y >= 0; --y)
        {
            for (int x = 0; x < width; ++x)
            {
                double u = double(x) / (width - 1);
                double v = double(y) / (height - 1);
                rt::Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
                rt::Color pixel_color = ray_color(r, world);
                DrawPixel(x, height - y, ColorFromNormalized(pixel_color.to_vector4(1)));
            }
        }
    }
    EndDrawing();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}