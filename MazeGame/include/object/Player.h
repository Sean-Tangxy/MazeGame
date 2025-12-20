// Player.h
#pragma once
#include "GameObject.h"

class Player : public GameObject {
private:
    int health;
    int speed;

public:
    Player(int x, int y);

    void update() override;
    void render() override;

    void move(int dx, int dy);
    void takeDamage(int damage);
    void heal(int amount);

    int getHealth() const;
    void setHealth(int h);
};