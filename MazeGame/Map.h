// Map.h
#pragma once
#include <vector>
#include <string>
#include <graphics.h>

class Map {
private:
    std::vector<std::vector<int>> grid;  // 0: ¿ÕµØ, 1: Ç½
    int cellSize;
    IMAGE wallImage;
    IMAGE floorImage;

public:
    Map(const std::string& filename);
    ~Map();

    void loadFromFile(const std::string& filename);
    void render();
    bool isWall(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
    int getCellSize() const;
};