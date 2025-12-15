// Key.cpp
#include "Key.h"
#include <iostream>

Key::Key(int x, int y) : Item(x, y, 16, 16) {
    tag = "Key";

    // 加载钥匙图片
    if (!loadImage("key.png")) {
        std::cout << "钥匙图片加载失败，使用默认图形" << std::endl;
    }
}

void Key::onCollect() {
    Item::onCollision(nullptr); // 调用基类方法
    std::cout << "获得钥匙! 现在可以打开出口" << std::endl;
}

void Key::render() {
    if (!isVisible() || isCollected()) return;

    // 如果有图片，使用图片渲染
    if (getwidth(&sprite) > 0) {
        GameObject::render();
    }
    else {
        // 否则绘制一个橙色圆形代表钥匙
        setfillcolor(RGB(255, 165, 0)); // 橙色
        solidcircle(position.x, position.y, width / 2);
    }
}