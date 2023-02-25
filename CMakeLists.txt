cmake_minimum_required(VERSION 3.16)

project(Raytracing)

add_subdirectory(src)

add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)