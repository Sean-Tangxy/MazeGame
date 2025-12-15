// Exit.cpp
#include "Exit.h"
#include <iostream>

Exit::Exit(int x, int y) : GameObject(x, y, 32, 32), locked(true) {
    tag = "Exit";

    // 加载出口图片
    if (!loadImage("exit.png")) {
        std::cout << "出口图片加载失败，使用默认图形" << std::endl;
    }
}

void Exit::update() {
    // 出口不需要每帧更新
}

void Exit::render() {
    if (!isVisible()) return;

    // 如果有图片，使用图片渲染
    if (getwidth(&sprite) > 0) {
        GameObject::render();
    }
    else {
        // 否则绘制一个绿色矩形代表出口
        setfillcolor(GREEN);
        fillrectangle(
            position.x - width / 2,
            position.y - height / 2,
            position.x + width / 2,
            position.y + height / 2
        );

        // 如果被锁住，绘制一个锁的标记
        if (locked) {
            setfillcolor(RED);
            solidrectangle(
                position.x - 5,
                position.y - 5,
                position.x + 5,
                position.y + 5
            );
        }
    }
}

void Exit::onCollision(GameObject* other) {
    if (other->getTag() == "Player") {
        if (locked) {
            std::cout << "出口被锁住了! 需要钥匙才能打开" << std::endl;
        }
        else {
            std::cout << "到达出口! 游戏胜利!" << std::endl;
            // 在实际游戏中，这里应该触发游戏胜利
        }
    }
}

bool Exit::isLocked() const {
    return locked;
}

void Exit::setLocked(bool l) {
    locked = l;
}