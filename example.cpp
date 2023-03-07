#include <iostream>
#include <fstream>
#include "node.h"
#include "json.hpp"
#include "flow.h"
using json = nlohmann::json;
int main() {
    std::ifstream ifs("../nodes.json");
    json j = json::parse(ifs);
    std::vector<Node> es = j.get<std::vector<Node>>();
    float maxFlow = flow(es);
    //json o;
    //o.emplace_back(es);
    std::cout << maxFlow << std::endl;
}