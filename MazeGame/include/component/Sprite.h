//cpp MazeGame\Sprite.h

#pragma once
#include <graphics.h>
#include <string>
#include <vector>

class Sprite {
private:
    IMAGE m_image;
    int m_frameWidth;
    int m_frameHeight;
    int m_frameCount;
    int m_currentFrame;
    int m_frameDelay; // Ö¡¼ä¸ô£¨ticks£©
    int m_tick;

public:
    Sprite();
    ~Sprite() = default;

    bool load(const std::string& file, int frameW = 0, int frameH = 0, int frames = 1);
    void update();
    void render(int x, int y);
    void reset();
};