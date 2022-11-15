#include <json.hpp>
#include <fstream>
#include <iostream>
#include <convex_hull.hpp>

using json = nlohmann::json;

int main()
{

    std::ifstream f("../convex_hulls.json");
    json data = json::parse(f);

    std::cout << "Original " << data << "\n\n\n";

    json dummy;
    json apexes = json::array();

    json x_val1;
    json x_val2;
    json x_val3;

    x_val1["x"] = 1;
    x_val1["y"] = 1;
    x_val2["x"] = 2;
    x_val2["y"] = 2;
    x_val3["x"] = 3;
    x_val3["y"] = 3;

    apexes.push_back(x_val1);
    apexes.push_back(x_val2);
    apexes.push_back(x_val3);

    dummy["apexes"] = apexes;
    dummy["ID"] = 0;

    json final_;

    json array = json::array();
    array.push_back(dummy);
    array.push_back(dummy);

    final_["convex hulls"] = array;

    std::cout << final_ << "\n";
}