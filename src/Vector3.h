
#ifndef VECTOR_UTILITY_H
#define VECTOR_UTILITY_H

#include "NumUtil.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

namespace Math {

class Vector3 {
public:
  constexpr Vector3() : x{0}, y{0}, z{0} {}
  constexpr Vector3(double x, double y, double z) : x{x}, y{y}, z{z} {}
  constexpr Vector3(const Vector3 &v) : x{v.x}, y{v.y}, z{v.z} {}
  constexpr auto operator+=(const Vector3 &v) -> Vector3 & {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  constexpr auto operator-=(const Vector3 &v) -> Vector3 & {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  constexpr auto operator*=(const Vector3 &v) -> Vector3 & {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  constexpr auto operator*=(double scalar) -> Vector3 & {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  constexpr auto operator/=(double scalar) -> Vector3 & {
    assert(scalar != 0 && "Divide vector by zero.");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }

  constexpr auto length() const -> double {
    return std::sqrt(x * x + y * y + z * z);
  }

  double x, y, z;
};

using Point3 = Vector3;

// Vector Utility Functions

inline auto operator<<(std::ostream &out, const Vector3 &v) -> std::ostream & {
  return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline auto operator+(const Vector3 &u, const Vector3 &v) -> Vector3 {
  return Vector3{u.x + v.x, u.y + v.y, u.z + v.z};
}

inline auto operator-(const Vector3 &u, const Vector3 &v) -> Vector3 {
  return Vector3{u.x - v.x, u.y - v.y, u.z - v.z};
}

inline auto operator*(const Vector3 &u, const Vector3 &v) -> Vector3 {
  return Vector3{u.x * v.x, u.y * v.y, u.z * v.z};
}

inline auto operator*(double t, const Vector3 &v) -> Vector3 {
  return Vector3{t * v.x, t * v.y, t * v.z};
}

inline auto operator*(const Vector3 &v, double t) -> Vector3 {
  return Vector3{t * v.x, t * v.y, t * v.z};
}

inline auto operator/(const Vector3 &v, double t) -> Vector3 {
  return Vector3{v.x / t, v.y / t, v.z / t};
}

inline auto dot(const Vector3 &u, const Vector3 &v) -> double {
  return u.x * v.x + u.y * v.y + u.z * v.z;
}

inline auto cross(const Vector3 &u, const Vector3 &v) -> Vector3 {
  return Vector3{u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
                 u.x * v.y - u.y * v.x};
}

inline auto unitVector(const Vector3 &v) -> Vector3 { return v / v.length(); }

inline auto randomVector(double min, double max) -> Vector3 {
  return Vector3{randomDouble(min, max), randomDouble(min, max),
                 randomDouble(min, max)};
}

inline auto randomUnitVector() -> Vector3 {
  while (true) {
    auto vector = randomVector(-1, 1);
    auto vec_length = vector.length() * vector.length();
    if (1e-160 <= vec_length && vec_length <= 1.0) {
      return vector / std::sqrt(vec_length);
    }
  }
}

inline auto randomOnHemisphere(const Vector3 &up_normal) -> Vector3 {
  auto vector = randomUnitVector();
  if (dot(up_normal, vector) > 0.0) {
    return vector;
  }
  return (-1.0 * vector);
}

} // namespace Math

#endif
