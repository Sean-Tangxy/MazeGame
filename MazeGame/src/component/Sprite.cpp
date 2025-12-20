//src\component\Sprite.cpp
#include "component/Sprite.h"

Sprite::Sprite()
    : m_frameWidth(0), m_frameHeight(0), m_frameCount(1),
    m_currentFrame(0), m_frameDelay(6), m_tick(0) {
}

bool Sprite::load(const std::string& file, int frameW, int frameH, int frames) {
    if (file.empty()) return false;
    if (loadimage(&m_image, file.c_str()) == 0) {
        // 如果没有指定帧大小，使用整张图片
        m_frameWidth = frameW > 0 ? frameW : m_image.getwidth();
        m_frameHeight = frameH > 0 ? frameH : m_image.getheight();
        m_frameCount = frames > 0 ? frames : 1;
        m_currentFrame = 0;
        m_tick = 0;
        return true;
    }
    return false;
}

void Sprite::update() {
    if (m_frameCount <= 1) return;
    ++m_tick;
    if (m_tick >= m_frameDelay) {
        m_tick = 0;
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
    }
}

void Sprite::render(int x, int y) {
    int sx = (m_currentFrame * m_frameWidth) % m_image.getwidth();
    int sy = (m_currentFrame * m_frameWidth) / m_image.getwidth() * m_frameHeight;
    putimage(x, y, m_frameWidth, m_frameHeight, &m_image, sx, sy);
}

void Sprite::reset() {
    m_currentFrame = 0;
    m_tick = 0;
}