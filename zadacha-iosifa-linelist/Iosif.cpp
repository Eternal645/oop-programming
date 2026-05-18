#include "LineList.h"
#include <ctime>
#include <iostream>

int main() {
    int N, k;
    std::cout << "Vvedite N: ";
    std::cin >> N;
    std::cout << "Vvedite k: ";
    std::cin >> k;

    clock_t start = clock();

    LineList<int> list;
    for (int i = 1; i <= N; i++)
        list.pushBack(i);

    auto* prev = list.advance(list.getHead(), N - 1);

    while (list.getSize() > 1) {
        prev = list.advance(prev, k - 1);
        list.removeAfter(prev);
    }

    int answer = list.getHead()->data;

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Otvet: " << answer << std::endl;
    std::cout << "Vremya: " << elapsed << " sek" << std::endl;

    return 0;
}
