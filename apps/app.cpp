// Using the google c++ style guide
#include <fstream>
#include <iostream>
#include <convex_hull.hpp>
#include <json.hpp>

using json = nlohmann::json;

int main()
{
    std::ifstream f("../convex_hulls.json");
    json data = json::parse(f);
    std::vector<ConvexHull> convex_hull_v;
    convex_hull_v = convexHullsFromJson(data);
    double overlap = 0.5;
    std::vector<ConvexHull> remaining_c_hulls = eliminateOverlappingCHulls(convex_hull_v, overlap);
    json remaining_c_hulls_json = convexHullsToJson(remaining_c_hulls);

    std::ofstream file("result_convex_hulls.json");
    file << std::setw(4) << remaining_c_hulls_json << std::endl;
    return 0;
}