// Potion.h - ҩˮ
#pragma once
#include "Item.h"

class Potion : public Item {
private:
    int healAmount;

public:
    Potion(int x, int y, int heal = 20);

    void onCollect() override;
    void render() override;

    int getHealAmount() const;
};