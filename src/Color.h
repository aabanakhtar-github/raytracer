#ifndef COLOR_H
#define COLOR_H

#include <ostream>

struct Color {
  double R = 0.0;
  double G = 0.0;
  double B = 0.0;
};

inline auto operator<<(std::ostream &out,
                       const Color &color) -> std::ostream & {
  return out << color.R * 255 << " " << color.G * 255 << " " << color.B * 255;
}

inline auto operator*(const Color &c, const double scale) -> Color {
  return {c.R * scale, c.G * scale, c.B * scale};
}

inline auto operator+(const Color &c, const Color &c2) -> Color {
  return {c.R + c2.R, c.G + c2.G, c.B + c2.B};
}

#endif // !COLOR_H
