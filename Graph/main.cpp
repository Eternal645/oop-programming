#include <iostream>
#include "Graph.h"

// BFS и DFS объявлены в Graph.cpp, повторим здесь для main
// (в реальном проекте их стоит вынести в отдельный заголовок)

#include <queue>
#include <set>

class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end) {
        std::queue<Node*> nodes; nodes.push(begin);
        std::set<Node*> visited;
        while (!nodes.empty()) {
            Node* next = nodes.front(); nodes.pop();
            if (end == next) return true;
            visited.insert(next);
            for (node_iterator it = next->nb_begin();
                 it != next->nb_end(); it++)
                if (visited.find(*it) == visited.end())
                    nodes.push(*it);
        }
        return false;
    }
};

class DFS {
    const Graph& graph;
    std::set<Node*> visited;
    bool connected(Node* begin, Node* end, int depth) {
        if (begin == end) return true;
        visited.insert(begin);
        for (node_iterator it = begin->nb_begin();
             it != begin->nb_end(); it++) {
            if (visited.find(*it) == visited.end()) {
                if (connected(*it, end, depth + 1)) return true;
            }
        }
        return false;
    }
public:
    DFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end) {
        visited.clear();
        return connected(begin, end, 0);
    }
};

int main() {
    // Граф из лекции: вершины 0-5
    Node n0("0"), n1("1"), n2("2"), n3("3"), n4("4"), n5("5");

    Graph g;
    g.addNode(&n0);
    g.addNode(&n1);
    g.addNode(&n2);
    g.addNode(&n3);
    g.addNode(&n4);
    g.addNode(&n5);

    // Рёбра из лекции
    g.addEdge(&n0, &n1);
    g.addEdge(&n1, &n2);
    g.addEdge(&n2, &n5);
    g.addEdge(&n0, &n5);
    g.addEdge(&n0, &n3);
    g.addEdge(&n3, &n4);
    g.addEdge(&n4, &n5);
    g.addEdge(&n1, &n3);
    g.addEdge(&n2, &n4);

    BFS bfs(g);
    DFS dfs(g);

    std::cout << "BFS: 0 -> 5 connected? "
              << (bfs.connected(&n0, &n5) ? "yes" : "no") << std::endl;
    std::cout << "DFS: 0 -> 5 connected? "
              << (dfs.connected(&n0, &n5) ? "yes" : "no") << std::endl;

    // Путь из лекции: (0, 3, 4, 5)
    std::cout << "BFS: 0 -> 2 connected? "
              << (bfs.connected(&n0, &n2) ? "yes" : "no") << std::endl;
    std::cout << "DFS: 0 -> 2 connected? "
              << (dfs.connected(&n0, &n2) ? "yes" : "no") << std::endl;

    return 0;
}
