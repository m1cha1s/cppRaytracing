#include <iostream>

extern "C"
{
#include <raylib.h>
}

int main()
{
    // Image
    const float aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = width / aspect_ratio;

    // Camera
    const float viewport_height = 2.0;
    const float viewport_width = aspect_ratio * viewport_height;
    const float focal_lenght = 1.0;

    InitWindow(width, height, "Raytracing");

    BeginDrawing();
    {
        ClearBackground(BLACK);
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