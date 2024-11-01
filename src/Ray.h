#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

namespace Math {

class Ray {
public:
  Ray() = default;

  Ray(const Point3 &origin, const Vector3 &direction)
      : origin_{origin}, direction_{direction} {}

  auto origin() const -> const Point3 & { return origin_; }
  auto direction() const -> const Vector3 & { return direction_; }

  auto at(double t) const -> Point3 { return origin_ + t * direction_; }

private:
  Point3 origin_;
  Vector3 direction_;
};

} // namespace Math

#endif
