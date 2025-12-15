// Map.cpp
#include "Map.h"
#include <fstream>
#include <sstream>
#include <iostream>

Map::Map(const std::string& filename) : cellSize(32) {
    loadFromFile(filename);

    // 加载墙壁和地板图片
    loadimage(&wallImage, _T("resources/images/wall.png"), cellSize, cellSize);
    loadimage(&floorImage, _T("resources/images/floor.png"), cellSize, cellSize);
}

Map::~Map() {
}

void Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开地图文件: " << filename << std::endl;
        // 创建默认地图
        grid = std::vector<std::vector<int>>(20, std::vector<int>(15, 0));
        for (int i = 0; i < 20; i++) {
            grid[i][0] = 1;
            grid[i][14] = 1;
        }
        for (int j = 0; j < 15; j++) {
            grid[0][j] = 1;
            grid[19][j] = 1;
        }
        return;
    }

    int width, height;
    file >> width >> height;

    grid.resize(width, std::vector<int>(height, 0));

    std::string line;
    std::getline(file, line); // 读取换行符

    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        for (int x = 0; x < width && x < line.length(); x++) {
            if (line[x] == '#') {
                grid[x][y] = 1; // 墙壁
            }
            else {
                grid[x][y] = 0; // 空地
            }
        }
    }

    file.close();
}

void Map::render() {
    // 渲染地板
    for (int x = 0; x < getWidth(); x++) {
        for (int y = 0; y < getHeight(); y++) {
            int screenX = x * cellSize;
            int screenY = y * cellSize;
            putimage(screenX, screenY, &floorImage);
        }
    }

    // 渲染墙壁
    for (int x = 0; x < getWidth(); x++) {
        for (int y = 0; y < getHeight(); y++) {
            if (grid[x][y] == 1) {
                int screenX = x * cellSize;
                int screenY = y * cellSize;
                putimage(screenX, screenY, &wallImage);
            }
        }
    }
}

bool Map::isWall(int x, int y) const {
    // 转换屏幕坐标到网格坐标
    int gridX = x / cellSize;
    int gridY = y / cellSize;

    if (gridX < 0 || gridX >= getWidth() || gridY < 0 || gridY >= getHeight()) {
        return true; // 边界外视为墙壁
    }

    return grid[gridX][gridY] == 1;
}

int Map::getWidth() const {
    return grid.size();
}

int Map::getHeight() const {
    return grid.empty() ? 0 : grid[0].size();
}

int Map::getCellSize() const {
    return cellSize;
}