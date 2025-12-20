#pragma once
#include <graphics.h>

class SceneManager; // 前置声明

class Scene {
public:
    virtual ~Scene() = default;
    virtual void init() = 0;
    virtual void processInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    // 可选回调，场景切换时会被调用
    virtual void onEnter() {}
    virtual void onExit() {}
};