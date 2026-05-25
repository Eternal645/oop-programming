#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>

static bool vectorContainsInt(const std::vector<int>& v, int val) {
    for (int x : v) if (x == val) return true;
    return false;
}

static bool vectorContainsStr(const std::vector<std::string>& v, const std::string& val) {
    for (const std::string& s : v) if (s == val) return true;
    return false;
}

static void sortVector(std::vector<int>& v) {
    for (int i = 0; i < (int)v.size(); i++)
        for (int j = i + 1; j < (int)v.size(); j++)
            if (v[j] < v[i]) { int tmp = v[i]; v[i] = v[j]; v[j] = tmp; }
}

static int minInt(int a, int b) { return a < b ? a : b; }
static int maxInt(int a, int b) { return a > b ? a : b; }

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

    std::vector<int> visited;
    std::queue<int> q;

    q.push(start_id);
    visited.push_back(start_id);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        visited_order.push_back(current);

        for (int neighbor : nodes[current].neighbors) {
            if (!vectorContainsInt(visited, neighbor)) {
                visited.push_back(neighbor);
                q.push(neighbor);
            }
        }
    }

    return visited_order;
}

// Выделение непересекающихся подграфов через BFS
void Graph::findAndSaveDisconnectedGraphs(const std::string& output_prefix) {
    std::vector<int> all_visited;
    int component_index = 0;

    // Собрать все id вершин
    std::vector<int> all_ids;
    for (auto& pair : nodes) {
        all_ids.push_back(pair.first);
    }

    for (int start_id : all_ids) {
        if (vectorContainsInt(all_visited, start_id)) continue;

        // BFS для данной компоненты связности
        std::vector<int> component;
        std::queue<int> q;
        q.push(start_id);
        component.push_back(start_id);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : nodes[current].neighbors) {
                if (!vectorContainsInt(component, neighbor)) {
                    component.push_back(neighbor);
                    q.push(neighbor);
                }
            }
        }

        // Отметить вершины как посещённые
        for (int id : component) {
            all_visited.push_back(id);
        }

        // Записать рёбра компоненты в файл
        std::string filename = output_prefix + std::to_string(component_index) + ".txt";
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            continue;
        }

        out << "Source\tTarget\n";

        std::vector<std::string> written_edges;
        sortVector(component);

        for (int node_id : component) {
            for (int neighbor : nodes[node_id].neighbors) {
                int a = minInt(node_id, neighbor);
                int b = maxInt(node_id, neighbor);
                std::string edge_key = std::to_string(a) + "_" + std::to_string(b);
                if (!vectorContainsStr(written_edges, edge_key)) {
                    written_edges.push_back(edge_key);
                    out << a << "\t" << b << "\n";
                }
            }
        }

        out.close();
        std::cout << "Компонента " << component_index
                  << ": " << component.size() << " вершин -> " << filename << std::endl;
        component_index++;
    }

    std::cout << "Всего непересекающихся подграфов: " << component_index << std::endl;
}
