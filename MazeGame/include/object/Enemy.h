// Enemy.h
#pragma once
#include "GameObject.h"
#include <utility>

class Enemy : public GameObject {
private:
    int speed;
    bool isChasing;
    std::pair<int, int> patrolPoints[2];
    int currentPatrolTarget;

public:
    Enemy(int x, int y);

    void update() override;
    void render() override;

    void chase(const std::pair<int, int>& targetPos);
    void patrol();
    void setPatrolPoints(const std::pair<int, int>& p1, const std::pair<int, int>& p2);
};