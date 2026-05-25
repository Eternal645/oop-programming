#include "Labirint.h"

#include <fstream>
#include <queue>
#include <cstring>
#include <stdexcept>

Image loadBMP(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open: " + path);

    BMPFileHeader fh;
    BMPInfoHeader ih;
    f.read(reinterpret_cast<char*>(&fh), sizeof(fh));
    f.read(reinterpret_cast<char*>(&ih), sizeof(ih));

    if (fh.signature != 0x4D42) throw std::runtime_error("Not a BMP file");
    if (ih.bitsPerPixel != 24)  throw std::runtime_error("Only 24-bit BMP supported");
    if (ih.compression  != 0)   throw std::runtime_error("Compressed BMP not supported");

    int w = ih.width;
    int h = (ih.height < 0) ? -ih.height : ih.height;
    bool topDown = (ih.height < 0);

    int rowBytes = ((w * 3 + 3) / 4) * 4; // выравнивание на 4 байта
    std::vector<uint8_t> rowBuf(rowBytes);

    Image img;
    img.width  = w;
    img.height = h;
    img.pixels.resize(h, std::vector<RGB>(w));

    f.seekg(fh.dataOffset, std::ios::beg);

    for (int row = 0; row < h; ++row) {
        f.read(reinterpret_cast<char*>(rowBuf.data()), rowBytes);
        int y = topDown ? row : (h - 1 - row);
        for (int x = 0; x < w; ++x) {
            img.pixels[y][x].b = rowBuf[x * 3 + 0];
            img.pixels[y][x].g = rowBuf[x * 3 + 1];
            img.pixels[y][x].r = rowBuf[x * 3 + 2];
        }
    }
    return img;
}

void saveBMP(const std::string& path, const Image& img) {
    int w = img.width, h = img.height;
    int rowBytes = ((w * 3 + 3) / 4) * 4;

    BMPFileHeader fh;
    BMPInfoHeader ih;
    memset(&fh, 0, sizeof(fh));
    memset(&ih, 0, sizeof(ih));

    fh.signature  = 0x4D42;
    fh.dataOffset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    fh.fileSize   = fh.dataOffset + rowBytes * h;

    ih.headerSize   = sizeof(BMPInfoHeader);
    ih.width        = w;
    ih.height       = h;
    ih.colorPlanes  = 1;
    ih.bitsPerPixel = 24;
    ih.imageSize    = rowBytes * h;

    std::ofstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot write: " + path);

    f.write(reinterpret_cast<const char*>(&fh), sizeof(fh));
    f.write(reinterpret_cast<const char*>(&ih), sizeof(ih));

    std::vector<uint8_t> rowBuf(rowBytes, 0);
    for (int row = 0; row < h; ++row) {
        int y = h - 1 - row; // BMP снизу вверх
        for (int x = 0; x < w; ++x) {
            rowBuf[x * 3 + 0] = img.pixels[y][x].b;
            rowBuf[x * 3 + 1] = img.pixels[y][x].g;
            rowBuf[x * 3 + 2] = img.pixels[y][x].r;
        }
        f.write(reinterpret_cast<const char*>(rowBuf.data()), rowBytes);
    }
}

// Классификация пикселей

bool isWall(const RGB& c) {
    return c.r < 50 && c.g < 50 && c.b < 50;
}

Point findColorCenter(const Image& img,
                      uint8_t minR, uint8_t maxR,
                      uint8_t minG, uint8_t maxG,
                      uint8_t minB, uint8_t maxB)
{
    long long sx = 0, sy = 0, cnt = 0;
    for (int y = 0; y < img.height; ++y)
        for (int x = 0; x < img.width; ++x) {
            const RGB& c = img.at(x, y);
            if (c.r >= minR && c.r <= maxR &&
                c.g >= minG && c.g <= maxG &&
                c.b >= minB && c.b <= maxB) {
                sx += x; sy += y; ++cnt;
            }
        }
    if (cnt == 0) throw std::runtime_error("Цветной маркер не найден");
    return { (int)(sx / cnt), (int)(sy / cnt) };
}

// Алгоритм Ли

static const int DX[] = { 0, 0, 1, -1 };
static const int DY[] = { 1,-1, 0,  0 };

std::vector<Point> leeSolve(const Image& img, Point start, Point end) {
    int W = img.width, H = img.height;

    std::vector<std::vector<int>> dist(H, std::vector<int>(W, -1));

    auto inBounds = [&](int x, int y) {
        return x >= 0 && x < W && y >= 0 && y < H;
    };

    auto passable = [&](int x, int y) {
        return !isWall(img.at(x, y));
    };

    std::queue<Point> q;
    dist[start.y][start.x] = 0;
    q.push(start);

    bool found = false;
    while (!q.empty() && !found) {
        Point cur = q.front(); q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = cur.x + DX[d];
            int ny = cur.y + DY[d];
            if (!inBounds(nx, ny)) continue;
            if (!passable(nx, ny)) continue;
            if (dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[cur.y][cur.x] + 1;
            q.push({nx, ny});
            if (nx == end.x && ny == end.y) { found = true; break; }
        }
    }

    if (!found) return {};

    // Восстановление пути обратным ходом
    std::vector<Point> path;
    Point cur = end;
    while (!(cur.x == start.x && cur.y == start.y)) {
        path.push_back(cur);
        for (int d = 0; d < 4; ++d) {
            int px = cur.x + DX[d];
            int py = cur.y + DY[d];
            if (!inBounds(px, py)) continue;
            if (dist[py][px] == dist[cur.y][cur.x] - 1) {
                cur = {px, py};
                break;
            }
        }
    }
    path.push_back(start);
    return path;
}
