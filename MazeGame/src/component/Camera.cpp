#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "component/Camera.h"
#include <cmath>
#include <graphics.h>

Camera::Camera(int width, int height)
    : m_x(0), m_y(0), m_width(width), m_height(height) {
}

void Camera::follow(GameObject* target, float lerp) {
    if (!target) return;
    auto pos = target->getPosition();
    int targetX = pos.x - m_width / 2;
    int targetY = pos.y - m_height / 2;
    m_x = static_cast<int>(m_x + (targetX - m_x) * lerp);
    m_y = static_cast<int>(m_y + (targetY - m_y) * lerp);
}

void Camera::apply() {
    setorigin(-m_x, -m_y);
}