#include <set>

float flow(std::vector<Edge> inputs) {
    std::map<int, Edge> edges;
    for(Edge edge : inputs) {
        edges[edge.id] = edge;
    }

    std::vector<std::set<int>> graph{{0}};

    for(int index = 0; graph[index].size() > 0; ++index) {
        graph.emplace_back(std::set<int>());
        for(int id: graph[index]) {
            Edge edge = edges[id];
            for(int nextId : edge.to) {
                graph[index + 1].insert(nextId);
                Edge nextEdge = edges[nextId];
                if(nextEdge.from.find(edge.weight) != nextEdge.from.end()){
                    nextEdge.from[edge.weight].insert(edge.id);
                } else {
                    nextEdge.from[edge.weight] = {edge.id};
                }
            }
        }
    }
    json o;
    o.emplace_back(graph);
    std::cout << o.dump() << std::endl;

}