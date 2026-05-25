#include "Labirint.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.bmp output.bmp\n";
        return 1;
    }

    try {
        std::cout << "Загрузка изображения..." << std::endl;
        Image img = loadBMP(argv[1]);
        std::cout << "Размер: " << img.width << " x " << img.height << std::endl;

        // Зелёный кружок: вход
        // Красный кружок: выход
        std::cout << "Поиск маркеров входа/выхода..." << std::endl;
        Point start = findColorCenter(img,   0, 100, 150, 255,   0, 100); // зелёный
        Point end   = findColorCenter(img, 150, 255,   0, 100,   0, 100); // красный

        std::cout << "Вход  (зелёный): (" << start.x << ", " << start.y << ")\n";
        std::cout << "Выход (красный): (" << end.x   << ", " << end.y   << ")\n";

        // Перекрашиваем маркеры в белый, чтобы они были проходимы для алгоритма
        for (int y = 0; y < img.height; ++y)
            for (int x = 0; x < img.width; ++x) {
                RGB& c = img.at(x, y);
                if (c.r < 100 && c.g > 150 && c.b < 100)
                    c = {255, 255, 255};
                if (c.r > 150 && c.g < 100 && c.b < 100)
                    c = {255, 255, 255};
            }

        std::cout << "Запуск волнового алгоритма Ли..." << std::endl;
        std::vector<Point> path = leeSolve(img, start, end);

        if (path.empty()) {
            std::cerr << "Путь не найден!\n";
            return 1;
        }
        std::cout << "Путь найден, длина: " << path.size() << " пикселей\n";

        // Рисуем путь синим цветом
        const RGB pathColor = {0, 0, 255};
        for (const Point& p : path)
            img.at(p.x, p.y) = pathColor;

        // Восстанавливаем маркеры поверх пути
        for (int dy = -5; dy <= 5; ++dy)
            for (int dx = -5; dx <= 5; ++dx)
                if (dx*dx + dy*dy <= 25) {
                    int nx = start.x + dx, ny = start.y + dy;
                    if (nx >= 0 && nx < img.width && ny >= 0 && ny < img.height)
                        img.at(nx, ny) = {34, 177, 76};
                }

        for (int dy = -5; dy <= 5; ++dy)
            for (int dx = -5; dx <= 5; ++dx)
                if (dx*dx + dy*dy <= 25) {
                    int nx = end.x + dx, ny = end.y + dy;
                    if (nx >= 0 && nx < img.width && ny >= 0 && ny < img.height)
                        img.at(nx, ny) = {237, 28, 36};
                }

        std::cout << "Сохранение результата..." << std::endl;
        saveBMP(argv[2], img);
        std::cout << "Готово: " << argv[2] << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
