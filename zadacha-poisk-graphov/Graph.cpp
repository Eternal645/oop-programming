#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// Node

Node::Node() : id(-1) {}

Node::Node(int id) : id(id) {}

void Node::addNeighbor(int neighbor_id) {
    neighbors.push_back(neighbor_id);
}

bool Node::hasNeighbor(int neighbor_id) const {
    for (int n : neighbors) {
        if (n == neighbor_id) return true;
    }
    return false;
}

// Graph

Graph::Graph() {}

// Конструктор, формирующий граф из файла
Graph::Graph(char* file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << file_name << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        int source, target;
        if (ss >> source >> target) {
            addEdge(source, target);
        }
    }

    file.close();
}

void Graph::addNode(int id) {
    if (nodes.find(id) == nodes.end()) {
        nodes[id] = Node(id);
    }
}

void Graph::addEdge(int source, int target) {
    addNode(source);
    addNode(target);
    if (!nodes[source].hasNeighbor(target)) {
        nodes[source].addNeighbor(target);
    }
    if (!nodes[target].hasNeighbor(source)) {
        nodes[target].addNeighbor(source);
    }
}

// BFS обход из заданной вершины, возвращает список посещённых вершин
std::vector<int> Graph::BFS(int start_id) {
    std::vector<int> visited_order;
    if (nodes.find(start_id) == nodes.end()) return visited_order;

    std::unordered_set<int> visited;
    std::queue<int> q;

    q.push(start_id);
    visited.insert(start_id);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        visited_order.push_back(current);

        for (int neighbor : nodes[current].neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    return visited_order;
}

// Выделение непересекающихся подграфов через BFS
// Каждый подграф записывается в отдельный файл
void Graph::findAndSaveDisconnectedGraphs(const std::string& output_prefix) {
    std::unordered_set<int> all_visited;
    int component_index = 0;

    // Собрать все id вершин и отсортировать для детерминированного порядка
    std::vector<int> all_ids;
    for (auto& pair : nodes) {
        all_ids.push_back(pair.first);
    }
    std::sort(all_ids.begin(), all_ids.end());

    for (int start_id : all_ids) {
        if (all_visited.find(start_id) != all_visited.end()) continue;

        // BFS для данной компоненты связности
        std::unordered_set<int> component_set;
        std::queue<int> q;
        q.push(start_id);
        component_set.insert(start_id);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : nodes[current].neighbors) {
                if (component_set.find(neighbor) == component_set.end()) {
                    component_set.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }

        // Отметить вершины как посещённые
        for (int id : component_set) {
            all_visited.insert(id);
        }

        // Записать рёбра компоненты в файл
        std::string filename = output_prefix + std::to_string(component_index) + ".txt";
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            continue;
        }

        out << "Source\tTarget\n";

        std::unordered_set<std::string> written_edges;
        std::vector<int> sorted_component(component_set.begin(), component_set.end());
        std::sort(sorted_component.begin(), sorted_component.end());

        for (int node_id : sorted_component) {
            for (int neighbor : nodes[node_id].neighbors) {
                // Записывать каждое ребро один раз
                int a = std::min(node_id, neighbor);
                int b = std::max(node_id, neighbor);
                std::string edge_key = std::to_string(a) + "_" + std::to_string(b);
                if (written_edges.find(edge_key) == written_edges.end()) {
                    written_edges.insert(edge_key);
                    out << a << "\t" << b << "\n";
                }
            }
        }

        out.close();
        std::cout << "Компонента " << component_index
                  << ": " << component_set.size() << " вершин -> " << filename << std::endl;
        component_index++;
    }

    std::cout << "Всего непересекающихся подграфов: " << component_index << std::endl;
}
