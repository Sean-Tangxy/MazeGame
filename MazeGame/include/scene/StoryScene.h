//include\scene\StoryScene.h

#pragma once
#include "scene/Scene.h"
#include "component/SceneManager.h"
#include "component/AudioManager.h"
#include <vector>
#include <string>

class StoryScene : public Scene {
private:
    SceneManager* m_manager;
    std::vector<std::string> m_images;
    size_t m_index;

public:
    StoryScene(SceneManager* mgr, const std::vector<std::string>& imgs);
    void init() override;
    void processInput() override;
    void update() override;
    void render() override;
    void onEnter() override;
    void onExit() override;
};