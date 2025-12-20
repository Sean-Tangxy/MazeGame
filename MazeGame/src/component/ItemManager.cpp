
#include "component/ItemManager.h"
#include <algorithm>
#include <iostream>


ItemManager::ItemManager() : exit(nullptr) {
}

ItemManager::~ItemManager() {
    if (exit) delete exit;
}

void ItemManager::initLevel() {
    // 清空现有物品
    items.clear();

    // 生成金币
    spawnCoin(100, 100, 10);
    spawnCoin(200, 150, 10);
    spawnCoin(300, 200, 10);
    spawnCoin(400, 250, 10);
    spawnCoin(500, 300, 10);

    // 生成药水
    spawnPotion(150, 200, 20);
    spawnPotion(350, 350, 20);

    // 生成钥匙
    spawnKey(600, 100);

    // 生成出口
    spawnExit(750, 550);
}

void ItemManager::update() {
    // 移除已收集的物品
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [](const std::unique_ptr<Item>& item) {
                return item->isCollected();
            }),
        items.end()
    );
}

void ItemManager::render() {
    // 渲染所有物品
    for (const auto& item : items) {
        item->render();
    }

    // 渲染出口
    if (exit) {
        exit->render();
    }
}

void ItemManager::checkCollisions(GameObject* obj) {
    // 检查与物品的碰撞
    for (const auto& item : items) {
        if (item->checkCollision(obj) && !item->isCollected()) {
            item->onCollision(obj);
        }
    }

    // 检查与出口的碰撞
    if (exit && exit->checkCollision(obj)) {
        exit->onCollision(obj);
    }
}

void ItemManager::spawnCoin(int x, int y, int value) {
    items.push_back(std::make_unique<Coin>(x, y, value));
}

void ItemManager::spawnPotion(int x, int y, int heal) {
    items.push_back(std::make_unique<Potion>(x, y, heal));
}

void ItemManager::spawnKey(int x, int y) {
    items.push_back(std::make_unique<Key>(x, y));
}

void ItemManager::spawnExit(int x, int y) {
    if (exit) delete exit;
    exit = new Exit(x, y);
}

bool ItemManager::hasKeyBeenCollected() const {
    for (const auto& item : items) {
        if (item->getTag() == "Key" && item->isCollected()) {
            return true;
        }
    }
    return false;
}

const std::vector<std::unique_ptr<Item>>& ItemManager::getItems() const
{
    return items;
}