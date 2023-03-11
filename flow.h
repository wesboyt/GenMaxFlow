#include <set>

void genGain(std::map<int, Node>& nodes, std::vector<std::set<int>> graph) {
    for(int i = 0; i < graph.size(); ++i) {
        for(int id : graph[i]) {
            float gain = nodes[id].currentGain;
            for(Edge& edge : nodes[id].to) {
                Node& nextNode = nodes[edge.to];
                float tempGain = gain * edge.weight;
                float nextGain = nextNode.currentGain;
                if(tempGain > nextGain) {
                    nextNode.currentGain = tempGain;
                }
                if(nextNode.fromGains.find(tempGain) != nextNode.fromGains.end()) {
                    nextNode.fromGains[tempGain].emplace_back(&edge);
                } else {
                    nextNode.fromGains[tempGain] = {&edge};
                }
            }
        }
    }
}

float flow(std::vector<Node> inputs, float initialFlow) {
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
            Node& node = nodes[id];
            for(Edge& edge: node.to) {
                if(used.find(edge.to) != used.end()) return -1.0;
                edge.from = id;
                graph[index + 1].insert(edge.to);
                nodes[edge.to].from.insert(id);
            }
        }
        used.insert(graph[index+1].begin(), graph[index+1].end());
    }

    graph.pop_back();

    Node& source = nodes[0];
    source.currentGain = 1.0;
    genGain(nodes, graph);
    Node sink = nodes[*((*(graph.rbegin())).begin())];

    int current = sink.id;
    std::vector<int> path{current};
    std::vector<Edge*> edges;
    while(current != source.id) {
        Edge* max = (*(nodes[current].fromGains.rbegin())).second[0];
        edges.emplace_back(max);
        int nextId = (*max).from;
        path.emplace_back(nextId);
        current = nextId;
    }

    std::reverse(path.begin(), path.end());
    std::reverse(edges.begin(), edges.end());


    current = source.id;
    float currentFlow = initialFlow;
    std::vector<float> updates{currentFlow};
    for(int i = 0; i < edges.size(); ++i) {
        currentFlow = currentFlow  * (*edges[i]).weight;
        updates.emplace_back(currentFlow);


    }

    o.clear();
    o.emplace_back(path);
    std::cout << o.at(0).dump() << std::endl;

    o.clear();
    o.emplace_back(nodes);
    std::cout << o.at(0).dump() << std::endl;


    return 5.0;
}