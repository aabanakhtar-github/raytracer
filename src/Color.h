#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

struct Color {
  std::uint8_t R, G, B, A;

  auto as_uint32_t() -> std::uint32_t {
    return (R << 24) + (G << 16) + (B << 8) + (A);
  }
};

#endif // !COLOR_H
