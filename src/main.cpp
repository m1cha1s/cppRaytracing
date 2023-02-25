#include <iostream>

#include "Ray.hpp"
#include "Vec3.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Hittable.hpp"
#include "Camera.hpp"
#include "Util.hpp"

extern "C"
{
#include <raylib.h>
}

rt::Color ray_color(const rt::Ray &r, const rt::Hittable &world, int depth)
{
    rt::HitRecord rec;

    if (depth <= 0)
        return rt::Color(0, 0, 0);
    if (world.hit(r, 0.001, INFINITY, rec))
    {
        rt::Point3 target = rec.p + rec.normal + rt::random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(rt::Ray(rec.p, target - rec.p), world, depth - 1);
    }
    rt::Vec3 unit_direction = rt::unit_vector(r.dir);
    double t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * rt::Color(1.0, 1.0, 1.0) + t * rt::Color(0.5, 0.7, 1.0);
}

void color_correction(rt::Color &pixel_color, int samples_per_pixel)
{

    double scale = 1.0 / samples_per_pixel;

    pixel_color *= scale;

    double r = clamp(sqrt(pixel_color.x), 0.0, 0.999);
    double g = clamp(sqrt(pixel_color.y), 0.0, 0.999);
    double b = clamp(sqrt(pixel_color.z), 0.0, 0.999);

    pixel_color = rt::Color(r, g, b);
}

int main()
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int width = 800;
    const int height = width / aspect_ratio;
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    rt::HittableList world;
    world.add(new rt::Sphere(rt::Point3(0, 0, -1), 0.5));
    world.add(new rt::Sphere(rt::Point3(0, -100.5, -1), 100));

    // Camera
    rt::Camera cam(aspect_ratio);

    InitWindow(width, height, "Raytracing");
    SetTargetFPS(10);

    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();

    for (int y = height - 1; y >= 0; --y)
    {
        BeginDrawing();
        for (int x = 0; x < width; ++x)
        {
            rt::Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                double u = double(x + random_double()) / (width - 1);
                double v = double(y + random_double()) / (height - 1);
                rt::Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            color_correction(pixel_color, samples_per_pixel);
            DrawPixel(x, height - y, ColorFromNormalized(to_vector4(pixel_color, 1)));
        }
        EndDrawing();
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}