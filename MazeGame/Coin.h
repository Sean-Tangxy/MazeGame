// Coin.h - ½ð±Ò
#pragma once
#include "Item.h"

class Coin : public Item {
private:
    int value;

public:
    Coin(int x, int y, int val = 10);

    void onCollect() override;
    void render() override;

    int getValue() const;
};