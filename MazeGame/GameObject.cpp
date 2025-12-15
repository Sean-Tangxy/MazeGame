// GameObject.cpp
#include "GameObject.h"
#include <iostream>

GameObject::GameObject(int x, int y, int w, int h)
    : position(x, y), width(w), height(h), visible(true), tag("GameObject") {
}

GameObject::~GameObject() {
}

void GameObject::render() {
    if (visible && !getwidth(&sprite) && !getheight(&sprite)) {
        putimage(position.x - width / 2, position.y - height / 2, &sprite);
    }
}

void GameObject::onCollision(GameObject* other) {
    // 基类不做任何事情，派生类可以重写
}

Position GameObject::getPosition() const {
    return position;
}

void GameObject::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

int GameObject::getWidth() const {
    return width;
}

int GameObject::getHeight() const {
    return height;
}

std::string GameObject::getTag() const {
    return tag;
}

bool GameObject::isVisible() const {
    return visible;
}

void GameObject::setVisible(bool v) {
    visible = v;
}

bool GameObject::checkCollision(const GameObject* other) const {
    if (!visible || !other->isVisible()) return false;

    int left1 = position.x - width / 2;
    int right1 = position.x + width / 2;
    int top1 = position.y - height / 2;
    int bottom1 = position.y + height / 2;

    int left2 = other->position.x - other->width / 2;
    int right2 = other->position.x + other->width / 2;
    int top2 = other->position.y - other->height / 2;
    int bottom2 = other->position.y + other->height / 2;

    return !(right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2);
}

bool GameObject::checkCollision(int x, int y, int w, int h) const {
    if (!visible) return false;

    int left1 = position.x - width / 2;
    int right1 = position.x + width / 2;
    int top1 = position.y - height / 2;
    int bottom1 = position.y + height / 2;

    int left2 = x - w / 2;
    int right2 = x + w / 2;
    int top2 = y - h / 2;
    int bottom2 = y + h / 2;

    return !(right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2);
}

bool GameObject::loadImage(const std::string& filename) {
    // 在EasyX中，通常使用相对路径
    // 这里我们假设图片在resources/images/目录下
    std::string fullPath = "resources/images/" + filename;

    // 转换字符串格式（如果需要）
    TCHAR tPath[256];
#ifdef _UNICODE
    MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, tPath, 256);
#else
    strcpy_s(tPath, fullPath.c_str());
#endif

    // 尝试加载图片
    loadimage(&sprite, tPath, width, height);

    // 检查是否加载成功
    return getwidth(&sprite) > 0 && getheight(&sprite) > 0;
}