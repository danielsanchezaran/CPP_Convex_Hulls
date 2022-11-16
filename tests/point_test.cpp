#include <convex_hull.hpp>
#include <iostream>

int main() {
  Point p1(100, 40);
  Point p2(50, -50);

  Point p3;
  p3 = p1 + p2;
  Point p4;
  p4 = p1 - p2;

  std::cout << "p1: (" << p1.x << ", " << p1.y << ")\n";
  std::cout << "p2: (" << p2.x << ", " << p2.y << ")\n";
  std::cout << "p3: (" << p3.x << ", " << p3.y << ")\n";
  std::cout << "p4: (" << p4.x << ", " << p4.y << ")\n";
  return 0;
}