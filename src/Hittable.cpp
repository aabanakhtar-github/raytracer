#include "Hittable.h"
#include "Vector3.h"

auto Sphere::hit(const Math::Ray &ray, double min_t, double max_t,
                 HitResult &hit) const -> bool {
  // definition of a circle
  // point x y z -> (x - x)^2 + (y - y)^2 + (z - z)^2 = r^2
  // or (center - point) dot (center - point)
  auto a = 1; // because we would be dotting the vector with itself and its
              // normalized
  auto oc = location_ - ray.origin();
  auto c = Math::dot(oc, oc) - radius_ * radius_;
  auto h = Math::dot(ray.direction(), oc);
  auto discriminant = h * h - a * c;
  if (discriminant < 0) {
    return false;
  }
  auto root = (-h - std::sqrt(discriminant)) /
              a; // choose the root based on the quadratic results
  if (root > max_t || root < min_t) {
    auto root2 = (-h + std::sqrt(discriminant)) / a;
    if (root2 > max_t || root2 < min_t) {
      return false;
    }
  }
  // fill in useful information
  hit.T = root;
  hit.Location = ray.direction() * hit.T;
  hit.Normal = Math::unitVector(ray.direction() - location_);
  return true;
}
