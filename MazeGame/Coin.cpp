// Coin.cpp
#include "Coin.h"
#include <iostream>

Coin::Coin(int x, int y, int val) : Item(x, y, 16, 16), value(val) {
    tag = "Coin";

    // 加载金币图片
    if (!loadImage("coin.png")) {
        std::cout << "金币图片加载失败，使用默认图形" << std::endl;
    }
}

void Coin::onCollect() {
    Item::onCollision(nullptr); // 调用基类方法
    std::cout << "收集到金币! 价值: " << value << std::endl;
}

void Coin::render() {
    if (!isVisible() || isCollected()) return;

    // 如果有图片，使用图片渲染
    if (getwidth(&sprite) > 0) {
        GameObject::render();
    }
    else {
        // 否则绘制一个黄色圆形代表金币
        setfillcolor(YELLOW);
        solidcircle(position.x, position.y, width / 2);
    }
}

int Coin::getValue() const {
    return value;
}