//include\scene\StartScene.h
#pragma once
#include "Scene.h"
#include <graphics.h>
#include <string>

class StartScene : public Scene {
public:
    StartScene();
    ~StartScene();

    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;

private:
    IMAGE m_background;
    IMAGE m_btnStart;
    bool m_btnLoaded;
    int m_btnX;
    int m_btnY;
    int m_btnW;
    int m_btnH;
    bool m_resourcesLoaded;
};