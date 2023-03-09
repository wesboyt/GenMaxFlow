#include <set>
#include "json.hpp"
using nlohmann::json;

struct Edge {
    float capacity;
    float weight;
    int to;
    int from;
};

void from_json(const json& j, Edge& e) {
    j.at("to").get_to(e.to);
    //j.at("from").get_to(e.from);
    j.at("capacity").get_to(e.capacity);
    j.at("weight").get_to(e.weight);
}

void to_json(json& j, const Edge& e) {
    j = json{
            {"capacity", e.capacity},
            {"weight", e.weight},
            {"to", e.to}
    };
}

struct Node {
    int id;
    std::vector<Edge> to;
    std::map<float, std::vector<Edge*>> fromGains;
    std::set<int> from;
};

void from_json(const json& j, Node& n) {
    j.at("id").get_to(n.id);
    j.at("to").get_to(n.to);
}

void to_json(json& j, const Node& n) {
    j = json{
            { "id", n.id},
            {"to", n.to},
            {"from", n.from}
    };
}