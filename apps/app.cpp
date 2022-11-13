//This code follows the Google C++ Style guide

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
    convex_hull_v = convexHullFromJson(data);
    std::cout << convex_hull_v[0].apex[0];
    return 0;
}