#pragma once

#include <vector>
#include <map>
#include <queue>
#include <string>

struct Node {
    int id;
    std::vector<int> neighbors;

    Node();
    Node(int id);

    void addNeighbor(int neighbor_id);
    bool hasNeighbor(int neighbor_id) const;
};

struct Graph {
    std::map<int, Node> nodes;

    Graph();
    Graph(char* file_name);

    void addNode(int id);
    void addEdge(int source, int target);
    void removeNode(int id);
    void removeEdge(int source, int target);

    std::vector<int> BFS(int start_id);
    void findAndSaveDisconnectedGraphs(const std::string& output_prefix);
};
