#include <iostream>
#include <fstream>
#include "edge.h"
#include "json.hpp"
#include "flow.h"
using json = nlohmann::json;
int main() {
    std::ifstream ifs("../edges.json");
    json j = json::parse(ifs);
    std::vector<Edge> es = j.get<std::vector<Edge>>();
    float maxFlow = flow(es);
    //json o;
    //o.emplace_back(es);
    std::cout << maxFlow << std::endl;
}