// Player.cpp
#include "Player.h"
#include <iostream>
#include <conio.h>

Player::Player(int x, int y) : GameObject(x, y, 32, 32), health(100), speed(5) {
    tag = "Player";

    // 加载玩家图片
    if (!loadImage("player.png")) {
        // 如果图片加载失败，使用矩形代替
        std::cout << "玩家图片加载失败，使用默认图形" << std::endl;
    }
}

void Player::update() {
    // 处理键盘输入
    if (GetAsyncKeyState('W') & 0x8000) {
        move(0, -speed);
    }
    if (GetAsyncKeyState('S') & 0x8000) {
        move(0, speed);
    }
    if (GetAsyncKeyState('A') & 0x8000) {
        move(-speed, 0);
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        move(speed, 0);
    }
}

void Player::render() {
    if (!isVisible()) return;

    // 如果有图片，使用图片渲染
    if (getwidth(&sprite) > 0) {
        GameObject::render();
    }
    else {
        // 否则绘制一个矩形代表玩家
        setfillcolor(GREEN);
        fillrectangle(
            position.x - width / 2,
            position.y - height / 2,
            position.x + width / 2,
            position.y + height / 2
        );

        // 绘制生命条
        int barWidth = 30;
        int barHeight = 4;
        int barX = position.x - barWidth / 2;
        int barY = position.y - height / 2 - 10;

        setfillcolor(RED);
        fillrectangle(barX, barY, barX + barWidth, barY + barHeight);

        setfillcolor(GREEN);
        fillrectangle(barX, barY, barX + (barWidth * health / 100), barY + barHeight);
    }
}

void Player::move(int dx, int dy) {
    // 在实际游戏中，这里应该检查碰撞
    position.x += dx;
    position.y += dy;

    // 确保不超出窗口边界
    if (position.x < width / 2) position.x = width / 2;
    if (position.x > 800 - width / 2) position.x = 800 - width / 2;
    if (position.y < height / 2) position.y = height / 2;
    if (position.y > 600 - height / 2) position.y = 600 - height / 2;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;

    std::cout << "玩家受到 " << damage << " 点伤害，剩余生命: " << health << std::endl;
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100) health = 100;

    std::cout << "玩家恢复 " << amount << " 点生命，当前生命: " << health << std::endl;
}

int Player::getHealth() const {
    return health;
}

void Player::setHealth(int h) {
    health = h;
}