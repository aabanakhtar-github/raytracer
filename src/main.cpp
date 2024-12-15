#include "Ray.h"
#include "Renderer.h"
#include "SDL3/SDL_events.h"
#include "Vector3.h"
#include <cstdint>
#include <iostream>

auto hitSphere(const Math::Point3 &center, double radius,
               const Math::Ray &r) -> double {
  // Calculate vector from ray origin to the sphere's center
  auto oc = center - r.origin();

  // a is the length squared of the ray direction (always 1.0 if normalized)
  auto a = dot(r.direction(), r.direction());

  // h is the dot product of the ray direction and the vector from the ray
  // origin to the sphere center
  auto h = dot(r.direction(), oc);

  // c is the length squared of the vector from ray origin to sphere center
  // minus the radius squared
  auto c = oc.length() * oc.length() - radius * radius;

  // Calculate the discriminant to check if there is an intersection
  auto discriminant = h * h - a * c;

  // If discriminant is negative, no intersection
  if (discriminant < 0.0) {
    return -1.0;
  } else {
    // Calculate the distance to the intersection
    return (-h - std::sqrt(discriminant)) / a;
  }
}

inline auto operator*(double scale, const Color &c) -> Color {
  return {c.R * scale, c.G * scale, c.B * scale};
}

auto getRayColor(const Math::Ray &r) -> Color {
  auto t = hitSphere({0.0, 0.0, -1.0}, 0.25, r);
  if (t > 0.0) {
    std::cout << "yes" << std::endl;
    auto hit_point = r.at(t);
    auto normal = Math::unitVector(hit_point - Math::Vector3{0.0, 0.0, -1.0});
    return 0.5 * Color{normal.x + 1.0, normal.y + 1.0, normal.z + 1.0};
  }
  auto start_color = Math::Vector3{0.0, 0.0, 1.0};
  auto end_color = Math::Vector3{1.0, 1.0, 1.0};
  // lerp based on y pos
  auto lerp_a = 0.5 * (Math::unitVector(r.direction()).y + 1.0);
  auto base = (1.0 - lerp_a) * end_color;
  auto mix = (lerp_a)*start_color;
  auto lerped = base + mix;
  return Color{1.0 * lerped.x, 1.0 * lerped.y, 1.0 * lerped.z};
}

auto raytracer(Renderer &renderer) -> void {
  constexpr static auto aspect_ratio =
      double(Renderer::getWidth()) / double(Renderer::getHeight());
  constexpr static auto viewport_height = 2.0;
  // scale the viewport width based on the height
  constexpr static auto viewport_width = viewport_height * aspect_ratio;
  const auto camera_center = Math::Vector3{0, 0, 0};
  // these vectors represent the width and height of the viewport
  // u = width
  // v = height
  const auto viewport_u = Math::Vector3{viewport_width, 0, 0};
  const auto viewport_v = Math::Vector3{0, -viewport_height, 0};
  // calculate the per pixel delta based on these values
  const auto delta_viewport_u = viewport_u / double(Renderer::getWidth());
  const auto delta_viewport_v = viewport_v / double(Renderer::getHeight());
  constexpr static auto focal_length =
      1.0; // this affects the FOV (the farther from the camera, the more zoomed
           // in)
  // first translate the camera's grid away from the center to avoid infinite
  // fov then shift up and left from the middle to the corner
  auto viewport_upper_left =
      (camera_center - Math::Vector3{0, 0, focal_length}) - viewport_u / 2 -
      viewport_v / 2;
  // now find the position of the top left pixel in world space, and then inset
  // it to be in the middle of the pixel (by delta in world space)
  auto pixel00_location =
      viewport_upper_left + 0.5 * (delta_viewport_u + delta_viewport_v);
  // render
  for (auto i = 0; i < Renderer::getHeight(); ++i) {
    for (auto j = 0; j < Renderer::getWidth(); ++j) {
      auto pixel_location = pixel00_location + double(j) * delta_viewport_u +
                            double(i) * delta_viewport_v;
      auto ray_direction = pixel_location - camera_center;
      ray_direction /= ray_direction.length();
      auto ray = Math::Ray{camera_center, ray_direction};
      auto color = getRayColor(ray);
      renderer.putPixel(j, i, color);
    }
  }
}

auto main(int argc, char *argv[]) -> int {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "Could not initalize SDL3!";
    return -1;
  }
  auto renderer = Renderer{};
  if (!renderer.getValid()) {
    std::cerr << "Failed to create a raytracing context!\n";
    return 1;
  }
  auto e = SDL_Event{};
  auto quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
    raytracer(renderer);
    renderer.clear();
  }

  SDL_Quit();
  std::cout << "test";
  return 0;
}
