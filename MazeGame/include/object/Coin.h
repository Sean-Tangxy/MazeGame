// Coin.h - ½ð±Ò
#pragma once
#include "../object/Coin.h"
#include "../object/Item.h"

class Coin : public Item {
private:
    int value;

public:
    Coin(int x, int y, int val = 10);

    void onCollect() override;
    void render() override;

    int getValue() const;
};