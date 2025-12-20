#pragma once

#include "Scene.h"

class TutorialScene : public Scene {
public:
    TutorialScene();
    virtual ~TutorialScene();

    void init() override;
    void onEnter() override;
    void onExit() override;
    void processInput() override;
    void update() override;
    void render() override;

private:
    bool m_loaded;
    unsigned long long m_lastTick;
};