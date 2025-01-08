#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
public:
  explicit Interval(double min, double max) : Min{min}, Max{max} {}

  auto size() const -> double { return Max - Min; }
  auto contains(double t) const -> bool { return Min <= t && t <= Max; }
  auto surrounds(double t) const -> bool { return Min < t && t < Max; }

  auto clamp(double x) const -> double {
    if (x > Max)
      return Max;
    if (x < Min)
      return Min;
    return x;
  }

  double Min, Max;
};

#endif
