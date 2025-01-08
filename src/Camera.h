#ifndef CAMERA_H
#define CAMERA_H

#include "Color.h"
#include "Hittable.h"
#include "Ray.h"
#include "Renderer.h"
#include "Vector3.h"

class Camera {
public:
  explicit Camera() {}
  auto doRaytrace(Renderer &renderer, const HittableList &world) -> void;

private:
  auto getRayColor(const Math::Ray &r, const HittableList &world) -> Color;
  auto getRay(double i, double j) -> Math::Ray;
  auto getRandomSquare() -> Math::Vector3;

private:
  constexpr static std::size_t samples_per_pixel_ = 10;
  constexpr static double sample_unit_factor_ =
      1.0 / double(samples_per_pixel_);
  constexpr static auto aspect_ratio =
      double(Renderer::getWidth()) / double(Renderer::getHeight());
  constexpr static auto viewport_height = 2.0;
  // scale the viewport width based on the height
  constexpr static auto viewport_width = viewport_height * aspect_ratio;
  const Math::Vector3 camera_center = Math::Vector3{0, 0, 0};
  // these vectors represent the width and height of the viewport
  // u = width
  // v = height
  constexpr static Math::Vector3 viewport_u =
      Math::Vector3{-viewport_width, 0, 0};
  constexpr static Math::Vector3 viewport_v =
      Math::Vector3{0, viewport_height, 0};
  // calculate the per pixel delta based on these values
  const static Math::Vector3 delta_viewport_u;
  const static Math::Vector3 delta_viewport_v;
  constexpr static auto focal_length =
      1.0; // this affects the FOV (the farther from the camera, the more
           // zoomed in)
};

#endif // CAMERA_H
