// Key.h - Ô¿³×
#pragma once
#include "Item.h"

class Key : public Item {
public:
    Key(int x, int y);

    void onCollect() override;
    void render() override;
};