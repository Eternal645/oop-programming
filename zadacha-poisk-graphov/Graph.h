#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
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
    std::unordered_map<int, Node> nodes;

    Graph();
    Graph(char* file_name);

    void addNode(int id);
    void addEdge(int source, int target);

    std::vector<int> BFS(int start_id);
    void findAndSaveDisconnectedGraphs(const std::string& output_prefix);
};
