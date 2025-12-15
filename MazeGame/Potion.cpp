// Potion.cpp
#include "Potion.h"
#include <iostream>

Potion::Potion(int x, int y, int heal) : Item(x, y, 16, 16), healAmount(heal) {
    tag = "Potion";

    // 加载药水图片
    if (!loadImage("potion.png")) {
        std::cout << "药水图片加载失败，使用默认图形" << std::endl;
    }
}

void Potion::onCollect() {
    Item::onCollision(nullptr); // 调用基类方法
    std::cout << "使用药水! 恢复: " << healAmount << " 点生命" << std::endl;
}

void Potion::render() {
    if (!isVisible() || isCollected()) return;

    // 如果有图片，使用图片渲染
    if (getwidth(&sprite) > 0) {
        GameObject::render();
    }
    else {
        // 否则绘制一个蓝色矩形代表药水
        setfillcolor(BLUE);
        fillrectangle(
            position.x - width / 2,
            position.y - height / 2,
            position.x + width / 2,
            position.y + height / 2
        );
    }
}

int Potion::getHealAmount() const {
    return healAmount;
}