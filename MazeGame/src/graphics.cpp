#include "MazeGame/include/graphics.h"
#include "MazeGame/include/gamemanager.h"

IMAGE::IMAGE(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID)
    : m_imageID(imageID), m_x(x), m_y(y), m_layer(layer), m_width(width), m_height(height), m_animID(animID), m_currentFrame(0) {
    GetObjects(m_layer).insert(this);
}

IMAGE::~IMAGE() {
    GetObjects(m_layer).erase(this);
}

bool IMAGE::operator==(const IMAGE& other) {
    return this == &other;
}

int IMAGE::GetX() const {
    return m_x;
}

int IMAGE::GetY() const {
    return m_y;
}

int IMAGE::getwidth() const {
    return m_width;
}

int IMAGE::getheight() const {
    return m_height;
}

AnimID IMAGE::GetCurrentAnimation() const {
    return m_animID;
}

void IMAGE::MoveTo(int x, int y) {
    m_x = x;
    m_y = y;
}

void IMAGE::ChangeImage(ImageID imageID) {
    m_imageID = imageID;
}

void IMAGE::PlayAnimation(AnimID animID) {
    m_animID = animID;
    m_currentFrame = 0;
}


std::set<IMAGE*>& IMAGE::GetObjects(LayerID layer) {
    static std::set<IMAGE*> gameObjects[MAX_LAYERS];
    if (auto l = static_cast<int>(layer); l < MAX_LAYERS)
        return  [l];
    else
        return gameObjects[0];
}
