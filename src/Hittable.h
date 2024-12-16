#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "Vector3.h"

struct HitResult {
  Math::Point3 Location;
  Math::Vector3 Normal;
  double T;
};

class Hittable {
public:
  virtual ~Hittable() = default;

  // out parameter
  virtual auto hit(const Math::Ray &ray, double min_t, double max_t,
                   HitResult &result) const -> bool = 0;
};

class Sphere : public Hittable {
public:
  explicit Sphere() {}

  auto hit(const Math::Ray &ray, double min_t, double max_t,
           HitResult &hit) const -> bool override;

  auto getRadius() const -> double { return radius_; }
  auto getLocation() const -> Math::Point3 { return location_; }

private:
  double radius_;
  Math::Point3 location_;
};

#endif // HITTABLE_H
