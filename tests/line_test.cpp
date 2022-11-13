#include <convex_hull.hpp>
#include <iostream>

int main()
{
    Point P1(0, 1);
    Point P2(0.707, 1.707);
    Line L1(P1, P2);

    Point P3(0, 2);
    Point P4(1, 1);
    Line L2(P3, P4);

    Point intersect;
    double eps = 0.0001;
    std::cout << "Intersect " << segmentsIntersect(L1, L2, intersect, eps) << "\n";
    std::cout << "point is " << intersect << "\n";
}