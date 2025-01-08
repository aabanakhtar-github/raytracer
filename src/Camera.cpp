#include "Camera.h"
#include "Vector3.h"

const Math::Vector3 Camera::delta_viewport_u =
    Camera::viewport_u / double(Renderer::getWidth());
const Math::Vector3 Camera::delta_viewport_v =
    Camera::viewport_v / double(Renderer::getHeight());

auto Camera::doRaytrace(Renderer &renderer, const HittableList &list) -> void {
  static auto viewport_upper_left =
      (camera_center - Math::Vector3{0, 0, focal_length}) - viewport_u / 2 -
      viewport_v / 2;
  // now find the position of the top left pixel in world space, and then
  // inset it to be in the middle of the pixel (by delta in world space)
  static auto pixel00_location =
      viewport_upper_left + 0.5 * (delta_viewport_u + delta_viewport_v);
  // render
  for (auto i = 0; i < Renderer::getHeight(); ++i) {
    for (auto j = 0; j < Renderer::getWidth(); ++j) {
      auto pixel_location = pixel00_location + double(j) * delta_viewport_u +
                            double(i) * delta_viewport_v;
      auto ray_direction = Math::unitVector(pixel_location - camera_center);
      // the color that holds the final aliased color
      auto pixel_color = Color{};
      for (std::size_t i = 0; i < samples_per_pixel_; ++i) {
        auto ray = getRay(i, j);
        pixel_color += getRayColor(ray);
      }
      renderer.putPixel(j, i, pixel_color * sample_unit_factor_);
    }
  }
}

auto Camera::getRayColor(const Math::Ray &r,
                         const HittableList &world) -> Color {
  auto result = HitResult{};
  if (world.hit(r, Interval{0, std::numeric_limits<double>::max()}, result)) {
    std::cout << result.Location.y << std::endl;
    auto &hit_point = result.Location;
    auto &normal = result.Normal;
    return Color{normal.x + 1.0, normal.y + 1.0, normal.z + 1.0} * 0.5;
  }
  auto start_color = Math::Vector3{0.0, 0.0, 1.0};
  auto end_color = Math::Vector3{1.0, 1.0, 1.0};
  // lerp based on y pos
  auto lerp_a = 0.5 * (Math::unitVector(r.direction()).y + 1.0);
  auto base = (1.0 - lerp_a) * end_color;
  auto mix = (lerp_a)*start_color;
  auto lerped = base + mix;
  auto clamper = Interval{0, 0.9999};
  return Color{clamper.clamp(1.0 * lerped.x), clamper.clamp(1.0 * lerped.y),
               clamper.clamp(1.0 * lerped.z)};
}
