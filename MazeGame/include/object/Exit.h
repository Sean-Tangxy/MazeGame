// Exit.h
#pragma once
#include "GameObject.h"
#include <utility>

class Exit : public GameObject {
private:
    bool locked;

public:
    Exit(int x, int y);

    void update() override;
    void render() override;
    void onCollision(GameObject* other) override;

    bool isLocked() const;
    void setLocked(bool l);
};