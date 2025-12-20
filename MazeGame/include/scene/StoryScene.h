#pragma once
#include "Scene.h"
#include <graphics.h>
#include <vector>
#include <string>

class StoryScene : public Scene {
public:
    StoryScene();
    ~StoryScene();

    void onEnter() override;
    void onExit() override;
    void update() override;
    void render() override;
    void init() override;
    void processInput() override;

private:
    std::vector<std::string> m_imagePaths;
    std::vector<IMAGE> m_images;
    std::vector<std::string> m_subtitles;
    int m_currentIndex;
    int m_displayMs;       // 每张图显示时间（毫秒）
    int m_elapsedMs;
    bool m_loaded;
    unsigned long long m_lastTick;
    bool m_showFinalTextOnly; // 用于第5条文本页
};