// Enemy.cpp
#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "../include/object/Enemy.h"
#include <cmath>
#include <graphics.h>

Enemy::Enemy(int x, int y) : GameObject(x, y, 32, 32), speed(3), isChasing(false), currentPatrolTarget(0) {
    tag = "Enemy";

    // 加载敌人图片
    if (!loadImage("enemy.png")) {
        std::cout << "敌人图片加载失败，使用默认图形" << std::endl;
    }

    // 初始化巡逻点
    patrolPoints[0] = std::make_pair(x - 100, y);
    patrolPoints[1] = std::make_pair(x + 100, y);

    // 随机数种子
    srand(static_cast<unsigned>(time(nullptr)));
}

void Enemy::update() {
    if (!isChasing) {
        patrol();
    }
}

void Enemy::render() {
    if (!isVisible()) return;

    // 如果有图片，使用图片渲染
    if (getwidth(&sprite) > 0) {
        GameObject::render();
    }
    else {
        // 否则绘制一个红色圆形代表敌人
        setfillcolor(RED);
        solidcircle(position.x, position.y, width / 2);
    }
}

// 修改函数签名以匹配头文件声明
void Enemy::chase(const std::pair<int, int>& targetPos) {
    isChasing = true;

    // 计算到目标的方向
    int dx = targetPos.first - position.x;
    int dy = targetPos.second - position.y;

    // 计算距离
    float distance = static_cast<float>(sqrt(static_cast<double>(dx * dx + dy * dy)));

    if (distance > 0) {
        // 归一化方向向量
        dx = static_cast<int>((dx / distance) * speed);
        dy = static_cast<int>((dy / distance) * speed);

        // 移动敌人
        position.x += dx;
        position.y += dy;
    }

    // 如果距离太远，停止追逐
    if (distance > 300) {
        isChasing = false;
    }
}

void Enemy::patrol() {
    if (patrolPoints[0].first == 0 && patrolPoints[0].second == 0) {
        return; // 巡逻点未设置
    }

    // 获取当前目标点
    std::pair<int, int> target = patrolPoints[currentPatrolTarget];

    // 计算到目标的方向
    int dx = target.first - position.x;
    int dy = target.second - position.y;

    // 计算距离
    float distance = static_cast<float>(sqrt(static_cast<double>(dx * dx + dy * dy)));

    if (distance < 5) {
        // 到达目标点，切换到下一个
        currentPatrolTarget = (currentPatrolTarget + 1) % 2;
    }
    else if (distance > 0) {
        // 归一化方向向量
        dx = static_cast<int>((dx / distance) * speed);
        dy = static_cast<int>((dy / distance) * speed);

        // 移动敌人
        position.x += dx;
        position.y += dy;
    }
}

void Enemy::setPatrolPoints(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    patrolPoints[0] = p1;
    patrolPoints[1] = p2;
}