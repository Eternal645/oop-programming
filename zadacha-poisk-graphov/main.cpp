#include <iostream>
#include "Graph.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <файл_графа> [префикс_выходных_файлов]" << std::endl;
        std::cerr << "Пример: " << argv[0] << " TestGraph.txt component_" << std::endl;
        return 1;
    }

    char* file_name = argv[1];
    std::string output_prefix = "component_";
    if (argc >= 3) {
        output_prefix = argv[2];
    }

    // Формирование графа из файла
    Graph g(file_name);
    std::cout << "Граф загружен: " << g.nodes.size() << " вершин" << std::endl;

    // Проверка корректности BFS
    if (!g.nodes.empty()) {
        int start_id = g.nodes.begin()->first;
        std::cout << "\nBFS из вершины " << start_id << ":" << std::endl;
        std::vector<int> bfs_result = g.BFS(start_id);
        std::cout << "Посещено вершин: " << bfs_result.size() << std::endl;
        std::cout << "Порядок обхода (первые 10):";
        for (int i = 0; i < (int)bfs_result.size() && i < 10; i++) {
            std::cout << " " << bfs_result[i];
        }
        if (bfs_result.size() > 10) std::cout << " ...";
        std::cout << std::endl;
    }

    // Выделение непересекающихся подграфов и запись в файлы
    std::cout << "\nВыделение непересекающихся подграфов:" << std::endl;
    g.findAndSaveDisconnectedGraphs(output_prefix);

    return 0;
}
