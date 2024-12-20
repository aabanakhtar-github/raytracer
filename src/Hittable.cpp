#include "Hittable.h"
#include "Vector3.h"
#include <iostream>

// goofy ahh math

auto Sphere::hit(const Math::Ray &ray, double min_t, double max_t,
                 HitResult &hit) const -> bool {
  // definition of a circle
  // point x y z -> (x - x)^2 + (y - y)^2 + (z - z)^2 = r^2
  // or (center - point) dot (center - point)
  auto a = 1.0; // because we would be dotting the vector with itself and its
                // normalized
  auto origin_to_center = location_ - ray.origin();
  auto c = Math::dot(origin_to_center, origin_to_center) - radius_ * radius_;
  auto h = Math::dot(ray.direction(), origin_to_center);
  auto discriminant = h * h - a * c;
  if (discriminant < 0) {
    return false;
  }
  // choose the most optimal root starting from the closest one and otherwise
  // the next closest
  auto root = (-h - std::sqrt(discriminant)) /
              a; // choose the root based on the quadratic results
  if (root >= max_t || root <= min_t) {
    auto root2 = (-h + std::sqrt(discriminant)) / a;
    if (root2 >= max_t || root2 <= min_t) {
      return false;
    }
    root = root2;
  }
  // fill in useful information
  hit.T = root;
  hit.Location = ray.direction() * hit.T;
  // determine the normal based on whether we are inside or outside the hit
  // surface. radius makes it a unit normal vector
  auto surface_normal =
      (hit.Location - location_) /
      radius_; // hit location - actual sphere location gives normal
  auto is_inside = isInside(surface_normal, ray.direction());
  hit.Normal = is_inside ? surface_normal * -1.0 : surface_normal;
  hit.IsHittingFrontFace = !is_inside;
  return true;
}

auto HittableList::hit(const Math::Ray &ray, double min_t, double max_t,
                       HitResult &out_result) const -> bool {
  auto closest_so_far = max_t;   // filters out anything that is farther than
                                 // necessary (higher T value)
  bool has_hit_anything = false; // returned
  auto temporary_hit_result = HitResult{}; // so that the funciton doesn't fill
                                           // invalid data if it doesn't hit
  for (const auto &hittable : hittables_) {
    if (hittable->hit(ray, min_t, closest_so_far, temporary_hit_result)) {
      // filter out anything with a higher T on next iter
      closest_so_far = temporary_hit_result.T;
      has_hit_anything = true;
      // oupdate the out parameter
      out_result = temporary_hit_result;
    }
  }
  return has_hit_anything;
}
