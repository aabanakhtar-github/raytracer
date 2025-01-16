#ifndef NUM_UTIL_H
#define NUM_UTIL_H

#include <random>

inline auto randomDouble() -> double {
  std::random_device rd;
  static auto dist = std::uniform_real_distribution<double>(0.0, 1.0);
  static auto gen = std::mt19937{rd()};
  return dist(gen);
}

inline auto randomDouble(double min, double max) {
  return min + (max - min) * randomDouble();
}

#endif // NUM_UTIL_H
