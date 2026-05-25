#pragma once

#include <string>
#include <vector>
#include <cstdint>

// BMP

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t  width;
    int32_t  height;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t  xPixelsPerMeter;
    int32_t  yPixelsPerMeter;
    uint32_t colorsInTable;
    uint32_t importantColors;
};
#pragma pack(pop)

struct RGB {
    uint8_t r, g, b;
};

struct Image {
    int width, height;
    std::vector<std::vector<RGB>> pixels;

    RGB&       at(int x, int y)       { return pixels[y][x]; }
    const RGB& at(int x, int y) const { return pixels[y][x]; }
};

struct Point {
    int x, y;
};

// Загрузка и сохранение 24-битного BMP
Image loadBMP(const std::string& path);
void  saveBMP(const std::string& path, const Image& img);

// Возвращает true если пиксель является стеной
bool isWall(const RGB& c);

// Находит центроид пикселей заданного цветового диапазона
Point findColorCenter(const Image& img,
                      uint8_t minR, uint8_t maxR,
                      uint8_t minG, uint8_t maxG,
                      uint8_t minB, uint8_t maxB);

// Волновой алгоритм Ли — возвращает путь от start до end
std::vector<Point> leeSolve(const Image& img, Point start, Point end);

