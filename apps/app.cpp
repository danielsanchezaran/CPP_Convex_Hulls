#include <json.hpp>
#include <fstream>
#include <iostream>
#include <convex_hull.hpp>

using json = nlohmann::json;

int main()
{

    std::ifstream f("../convex_hulls.json");
    json data = json::parse(f);
    // std::cout << data << "\n";
    std::cout << data["convex hulls"].size() << "\n";

    std::vector<ConvexHull> convex_hull_v;
    convex_hull_v = convexHullsFromJson(data);
    std::cout << convex_hull_v[0].apex[0] << "\n";

    std::vector<Point> vertex;
    Point P1(-1, -1);
    Point P2(-1, 1);
    Point P3(1, 1);
    Point P4(1, -1);
    vertex.push_back(P1);
    vertex.push_back(P2);
    vertex.push_back(P3);
    vertex.push_back(P4);

    ConvexHull C(vertex, 0);

    std::vector<Point> vertex2;
    Point P12(0, 0);
    Point P22(-0.5, -1.1);
    Point P32(0.5, -1.1);
    vertex2.push_back(P12);
    vertex2.push_back(P22);
    vertex2.push_back(P32);

    ConvexHull C2(vertex2, 0);
    std::vector<Point> vertex3;
    ConvexHull interC(vertex, 0);
    bool intersection = getIntersectingPolygon(C, C2, interC);
    std::cout << "they intersect: " << intersection << "\n";
    std::cout << "inner polygon is: \n";
    if (intersection)
    {
        for (Point p : interC.apex)
        {
            std::cout << p << "\n";
        }
    }

    Point Pin(0, 0);
    Point Pout(1, 1);
    Point P3_(0.5, 0);
    Point P4_(0.5, 1);

    std::cout << "Pin Inside " << C.isPointInside(Pin) << "\n";
    std::cout << "Pout Inside " << C.isPointInside(Pout) << "\n";

    Line L1(Pin, Pout);
    Line L2(P3_, P4_);
    Point inter;
    double eps = 0.00001;
    std::cout << "intersect: " << segmentsIntersect(L1, L2, inter, eps) << "\n";
    std::cout << "inter point " << inter << "\n";

    return 0;
}