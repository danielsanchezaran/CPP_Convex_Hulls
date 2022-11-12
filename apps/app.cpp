//This code follows the Google C++ Style guide

#include <json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

int main()
{

    std::ifstream f("convex_hulls.json");
    json data = json::parse(f);
    // std::cout << data << "\n";
    std::cout << data["convex hulls"].size() <<"\n";
    return 0;
}