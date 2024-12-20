#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Vector3.h"
#include <list>
#include <memory>

struct HitResult {
  Math::Point3 Location;
  Math::Vector3 Normal;
  double T;
  bool IsHittingFrontFace;
};

inline auto isInside(const Math::Vector3 &surfaceNormal,
                     const Math::Vector3 &attackVector) -> bool {
  if (Math::dot(surfaceNormal, attackVector) > 0.0) {
    // the ray is inside the the surface
    return true;
  }
  // otherwise its on the outside (facing opposite general directions)
  return false;
}

class Hittable {
public:
  virtual ~Hittable() = default;

  // out parameter
  virtual auto hit(const Math::Ray &ray, double min_t, double max_t,
                   HitResult &result) const -> bool = 0;
};

class Sphere : public Hittable {
public:
  explicit Sphere(double radius, const Math::Point3 &location)
      : radius_{radius}, location_{location} {}

  auto hit(const Math::Ray &ray, double min_t, double max_t,
           HitResult &hit) const -> bool override;

  auto getRadius() const -> double { return radius_; }
  auto getLocation() const -> Math::Point3 { return location_; }

private:
  double radius_;
  Math::Point3 location_;
};

class HittableList {
public:
  using ListType = std::list<std::shared_ptr<Hittable>>;
  HittableList(ListType &l) : hittables_{std::move(l)} {}

  auto addNew(std::shared_ptr<Hittable> &h) -> void {
    hittables_.push_back(std::move(h));
  }

  auto hit(const Math::Ray &ray, double min_t, double max_t,
           HitResult &out_result) const -> bool;

private:
  ListType hittables_;
};

#endif // HITTABLE_H
