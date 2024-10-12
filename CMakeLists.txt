cmake_minimum_required(VERSION 3.26)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_subdirectory(vendor/SDL)

add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/Renderer.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3-shared)
