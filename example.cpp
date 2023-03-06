#include <iostream>
#include <fstream>
#include "edge.h"
#include "json.hpp"
using json = nlohmann::json;
int main() {
    std::ifstream ifs("../edges.json");
    json j = json::parse(ifs);
    std::vector<Edge> es = j.get<std::vector<Edge>>();
    json o;
    o.emplace_back(es);
    std::cout << o.dump() << std::endl;
}