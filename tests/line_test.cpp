#include <convex_hull.hpp>
#include <iostream>

int main() {
  Point P1(8.64869, 17.23681);
  Point P2(7.05143, 16.39631);
  Line L1(P1, P2);

  Point P3(8.2447, 18.4155);
  Point P4(8.0056, 15.5648);
  Line L2(P3, P4);

  Point intersect;
  double eps = 0.0001;
  std::cout << "Intersect " << segmentsIntersect(&L2, &L1, &intersect, eps)
            << "\n";
  std::cout << "point is " << intersect << "\n";
}
