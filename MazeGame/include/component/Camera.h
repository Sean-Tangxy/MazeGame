#pragma once
#include "../object/GameObject.h"

class Camera {
private:
    int m_x, m_y;
    int m_width, m_height;

public:
    Camera(int width = 800, int height = 600);
    void follow(GameObject* target, float lerp = 0.2f);
    void apply(); // 将坐标系平移到相机视角
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    void setSize(int w, int h) { m_width = w; m_height = h; }
};