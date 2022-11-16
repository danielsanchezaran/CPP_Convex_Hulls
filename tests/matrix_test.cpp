#include <iostream>

#include <convex_hull.hpp>

int main() {
  Point p1(100, 40);
  Point p2(50, -50);

  Matrix M1(p1, p2);
  Matrix M2(p2, p1);
  std::cout << M1;
  std::cout << M2;
  Matrix M3;
  M3 = M1 * 2;
  std::cout << M3;
  M3 = M1 + M2;
  std::cout << M3;
  std::cout << "det: " << M1.getDeterminant() << "\n";

  return 0;
}
