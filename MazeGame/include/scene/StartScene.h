//include\scene\StartScene.h
#pragma once
#include "scene/Scene.h"
#include "component/SceneManager.h"
#include "component/AudioManager.h"
#include <string>

class StartScene : public Scene {
private:
    SceneManager* m_manager;
    std::string m_bgPath;
    bool m_buttonPressed;

public:
    StartScene(SceneManager* mgr, const std::string& bg = "");
    void init() override;
    void processInput() override;
    void update() override;
    void render() override;
    void onEnter() override;
    void onExit() override;
};