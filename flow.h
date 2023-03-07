#include <set>

std::map<int,float> genGain(std::map<int, Node> *nodes, std::vector<std::set<int>> graph) {
    std::map<int,float> gains;
    for(auto node : (*nodes)) {
        gains[node.first] = 0.0;
    }
    gains[0] = 1.0;

    for(int i = 0; i < graph.size(); ++i) {
        for(int id : graph[i]) {
            float gain = gains[id];
            for(int i = 0; i < (*nodes)[id].to.size(); ++i) {
                Edge edge = (*nodes)[id].to[i];
                float tempGain = gain * edge.weight;
                float nextGain = gains[edge.to];
                if(tempGain > nextGain) {
                    gains[edge.to] = tempGain;
                }
                if((*nodes)[edge.to].fromGains.find(tempGain) != (*nodes)[edge.to].fromGains.end()) {
                    (*nodes)[edge.to].fromGains[tempGain].emplace_back(&((*nodes)[id].to[i]));
                } else {
                    (*nodes)[edge.to].fromGains[tempGain] = {&((*nodes)[id].to[i])};
                }
            }
        }
    }
    return gains;
}

float flow(std::vector<Node> inputs) {
    json o;
    std::map<int, Node> nodes;
    for(Node node : inputs) {
        nodes[node.id] = node;
    }

    std::vector<std::set<int>> graph{{0}};
    std::set<int> used{0};

    for(int index = 0; graph[index].size() > 0; ++index) {
        graph.emplace_back(std::set<int>());
        for(int id: graph[index]) {
            Node node = nodes[id];
            for(Edge edge : node.to) {
                if(used.find(edge.to) != used.end()) return -1.0;
                edge.from = id;
                graph[index + 1].insert(edge.to);
                nodes[edge.to].from.insert(id);
            }
        }
        used.insert(graph[index+1].begin(), graph[index+1].end());
    }

    graph.pop_back();

    Node source = nodes[0];

    auto gains = genGain(&nodes, graph);

    Node sink = nodes[*(graph[graph.size() - 1].begin())];
    o.emplace_back(sink);
    std::cout << o.at(0).dump() << std::endl;
    auto it = sink.fromGains.end();
    it--;
    std::cout << it->first << std::endl;

    /*
    o.clear();
    o.emplace_back(gains);
    std::cout << o.at(0).dump() << std::endl;

    o.clear();
    o.emplace_back(nodes);
    std::cout << o.at(0).dump() << std::endl;
     */

    return 5.0;
}