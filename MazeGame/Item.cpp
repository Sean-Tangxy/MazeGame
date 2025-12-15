// Item.cpp
#include "Item.h"

Item::Item(int x, int y, int w, int h) : GameObject(x, y, w, h), collected(false) {
    tag = "Item";
}

void Item::update() {
    // 物品通常不需要每帧更新
}

void Item::onCollision(GameObject* other) {
    if (other->getTag() == "Player" && !collected) {
        collected = true;
        visible = false;
    }
}

bool Item::isCollected() const {
    return collected;
}

void Item::setCollected(bool c) {
    collected = c;
    visible = !c; // 收集后不可见
}