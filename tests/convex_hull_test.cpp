#include <convex_hull.hpp>
#include <iostream>

int main() {
  Point p1(4, 10);
  Point p2(4, 4);
  Point p3(11, 2);
  Point p4(2, 2);

  std::vector<Point> apexes;
  apexes.push_back(p1);
  apexes.push_back(p2);
  apexes.push_back(p3);
  apexes.push_back(p4);

  ConvexHull c_hull(apexes, 0);
  std::cout << "Area is " << c_hull.getArea() << "\n";
  return 0;
}