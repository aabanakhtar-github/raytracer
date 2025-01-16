#include "Camera.h"
#include "NumUtil.h"
#include "Vector3.h"

const Math::Vector3 Camera::delta_viewport_u =
    Camera::viewport_u / double(Renderer::getWidth());
const Math::Vector3 Camera::delta_viewport_v =
    Camera::viewport_v / double(Renderer::getHeight());

auto Camera::doRaytrace(Renderer &renderer, const HittableList &list) -> void {
  // now find the position of the top left pixel in world space, and then
  for (auto i = 0; i < Renderer::getHeight(); ++i) {
    for (auto j = 0; j < Renderer::getWidth(); ++j) {
      // the color that holds the final aliased color
      auto pixel_color = Color{0, 0, 0};
      for (std::size_t k = 0; k < samples_per_pixel_; ++k) {
        auto ray = getRay(i, j);
<<<<<<< HEAD
        pixel_color = pixel_color + getRayColor(ray, list);
=======
        pixel_color = pixel_color + getRayColor(ray, list, max_bounces_);
>>>>>>> f8c7a41 (.)
      }
      renderer.putPixel(j, i, pixel_color * sample_unit_factor_);
    }
  }
}

auto Camera::getRay(double i, double j) -> Math::Ray {
  static auto viewport_upper_left =
      (camera_center - Math::Vector3{0, 0, focal_length}) - viewport_u / 2 -
      viewport_v / 2;
  static auto pixel00_location =
      viewport_upper_left + 0.5 * (delta_viewport_u + delta_viewport_v);
  auto sample_offset = getRandomSquare();
  auto pixel_location = pixel00_location +
                        double(j + sample_offset.x) * delta_viewport_u +
                        double(i + sample_offset.y) * delta_viewport_v;
  auto ray_direction = Math::unitVector(pixel_location - camera_center);
  return Math::Ray{camera_center, ray_direction};
}

auto Camera::getRandomSquare() -> Math::Vector3 {
  return Math::Vector3{randomDouble() - 0.9, randomDouble() - 0.9, 0};
}

auto Camera::getRayColor(const Math::Ray &r, const HittableList &world,
                         std::size_t bounce_count) -> Color {
  // to prevent infinite bounces
  if (bounce_count <= 0) {
    return Color{0, 0, 0};
  }
  auto result = HitResult{};
  if (world.hit(r, Interval{0.01, 6000}, result)) {
    auto &hit_point = result.Location;
    auto normal = Math::unitVector(result.Normal);
    // diffuse scattering
    auto nextDirection = Math::randomOnHemisphere(normal);
    // std::cout << Math::dot(nextDirection, normal) << "\n";
    return getRayColor(Math::Ray{hit_point, nextDirection}, world,
                       bounce_count - 1) *
           0.5;
  }
  return {0.0, 0.01, 0.03};
  auto start_color = Math::Vector3{0.0, 0.0, 1.0};
  auto end_color = Math::Vector3{1.0, 1.0, 1.0};
  // lerp based on y pos
  auto lerp_a = 0.5 * (Math::unitVector(r.direction()).y + 1.0);
  auto base = (1.0 - lerp_a) * end_color;
  auto mix = (lerp_a)*start_color;
  auto lerped = base + mix;
  auto clamper = Interval{0, 1};
  return Color{clamper.clamp(1.0 * lerped.x), clamper.clamp(1.0 * lerped.y),
               clamper.clamp(1.0 * lerped.z)};
}
