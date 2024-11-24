#include <iostream>
#include <cmath>
#include <random>

bool IsPointInside(double x, double y, double center_x, double center_y, double radius) {
  return std::pow(x - center_x, 2) + std::pow(y - center_y, 2) <= radius * radius;
}

double ComputeMonteCarlo(double start_x, double start_y, double width, double height, size_t samples, auto region_check) {
  std::random_device random_device;
  std::mt19937 engine(random_device());
  std::uniform_real_distribution<double> uniform_dist(0, 1);

  size_t count = 0;
  for (size_t i = 0; i < samples; ++i) {
    double x = start_x + uniform_dist(engine) * width;
    double y = start_y + uniform_dist(engine) * height;
    if (region_check(x, y)) {
      ++count;
    }
  }
  return (static_cast<double>(count) / samples) * width * height;
}

int main() {
  double cx1 = NAN;
  double cy1 = NAN;
  double r1 = NAN;
  double cx2 = NAN;
  double cy2 = NAN;
  double r2 = NAN;
  double cx3 = NAN;
  double cy3 = NAN;
  double r3 = NAN;
  std::cin >> cx1 >> cy1 >> r1 >> cx2 >> cy2 >> r2 >> cx3 >> cy3 >> r3;

  auto check_region = [&](double x, double y) {
    return IsPointInside(x, y, cx1, cy1, r1) &&
           IsPointInside(x, y, cx2, cy2, r2) &&
           IsPointInside(x, y, cx3, cy3, r3);
  };

  double x_min = std::min(cx1 - r1, std::min(cx2 - r2, cx3 - r3));
  double y_min = std::min(cy1 - r1, std::min(cy2 - r2, cy3 - r3));
  double x_max = std::max(cx1 + r1, std::max(cx2 + r2, cx3 + r3));
  double y_max = std::max(cy1 + r1, std::max(cy2 + r2, cy3 + r3));

  double width = x_max - x_min;
  double height = y_max - y_min;

  double result = ComputeMonteCarlo(x_min, y_min, width, height, 1000000, check_region);
  std::cout << result << std::endl;
  return 0;
}
