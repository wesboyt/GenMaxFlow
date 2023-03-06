#include "json.hpp"
using nlohmann::json;

struct Edge {
    int id;
    float capacity;
    float weight;
    std::vector<int> to;
};

void from_json(const json& j, Edge& e) {
    j.at("id").get_to(e.id);
    j.at("capacity").get_to(e.capacity);
    j.at("weight").get_to(e.weight);
    j.at("to").get_to(e.to);
}

void to_json(json& j, const Edge& e) {
    j = json{
            { "id", e.id,},
            {"capacity", e.capacity},
            {"weight", e.weight},
            {"to", e.to}
    };
}