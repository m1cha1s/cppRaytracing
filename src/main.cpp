#include <iostream>

#include "Ray.hpp"
#include "Vec3.hpp"

extern "C"
{
#include <raylib.h>
}

double hit_sphere(const rt::Point3 &center, double radius, const rt::Ray r)
{
    rt::Vec3 oc = r.orig - center;
    double a = r.dir.lenght_sq();
    double half_b = dot(oc, r.dir);
    double c = oc.lenght_sq() - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return -1;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

rt::Color ray_color(const rt::Ray &r)
{
    double t = hit_sphere(rt::Point3(0, 0, -1), 0.5, r);
    if (t > 0)
    {
        rt::Vec3 N = rt::unit_vector(r.at(t) - rt::Vec3(0, 0, -1));
        return 0.5 * rt::Color(N.x + 1, N.y + 1, N.z + 1);
    }
    rt::Vec3 unit_direction = rt::unit_vector(r.dir);
    t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * rt::Color(1.0, 1.0, 1.0) + t * rt::Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = width / aspect_ratio;

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
                rt::Color pixel_color = ray_color(r);
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