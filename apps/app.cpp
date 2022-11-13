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
    std::cout << data["convex hulls"].size() <<"\n";

    std::vector<ConvexHull> convex_hull_v;
    convex_hull_v = convexHullsFromJson(data);
    std::cout << convex_hull_v[0].apex[0] <<"\n";

    std::vector<Point> vertex;
    Point P1(-1,1);
    Point P2(1,1);
    Point P3(1,-1);
    Point P4(-1,-1);
    vertex.push_back(P1);
    vertex.push_back(P2);
    vertex.push_back(P3);
    vertex.push_back(P4);

    ConvexHull C(vertex,0);

    Point Pin(0,0);
    Point Pout(1.01 ,1);

    std::cout << "Pin Inside " << C.isPointInside(Pin) << "\n";
    std::cout << "Pout Inside " << C.isPointInside(Pout) << "\n";
    return 0;
}