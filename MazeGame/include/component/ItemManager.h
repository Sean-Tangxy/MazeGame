// ItemManager.h
#pragma once
#include <vector>
#include <memory>
#include "object/Coin.h"
#include "object/Potion.h"
#include "object/Key.h"
#include "object/Exit.h"

class ItemManager {
private:
    std::vector<std::unique_ptr<Item>> items;
    Exit* exit;

public:
    ItemManager();
    ~ItemManager();

    void initLevel();
    void update();
    void render();

    void checkCollisions(GameObject* obj);
    void spawnCoin(int x, int y, int value = 10);
    void spawnPotion(int x, int y, int heal = 20);
    void spawnKey(int x, int y);
    void spawnExit(int x, int y);

    bool hasKeyBeenCollected() const;

    const std::vector<std::unique_ptr<Item>>& getItems() const;
};