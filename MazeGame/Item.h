// Item.h - 基类
#pragma once
#include "GameObject.h"

class Item : public GameObject {
protected:
    bool collected;

public:
    Item(int x, int y, int w, int h);  // 修复：添加w, h参数
    virtual ~Item() = default;

    virtual void update() override;
    //virtual void render() override;         Q?
    virtual void onCollision(GameObject* other) override;  // 添加：声明碰撞函数
    virtual void onCollect() = 0;  // 纯虚函数

    bool isCollected() const;
    void setCollected(bool c);
};