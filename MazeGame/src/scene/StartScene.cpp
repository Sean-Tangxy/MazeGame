//cpp MazeGame\StartScene.cpp
#include "../include/scene/StartScene.h"
#include <Windows.h>

StartScene::StartScene(SceneManager* mgr, const std::string& bg)
    : m_manager(mgr), m_bgPath(bg), m_buttonPressed(false) {
}

void StartScene::init() {
    // 可以开始加载图像/资源
}

void StartScene::onEnter() {
    // 播放背景音乐（示例）
    AudioManager::playMusic("Assets/music/title.wav", true);
}

void StartScene::onExit() {
    AudioManager::stopMusic();
}

void StartScene::processInput() {
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        POINT mp;
        if (GetCursorPos(&mp)) {
            ScreenToClient(GetHWnd(), &mp);
            // 简单按钮区域判断
            if (mp.x >= 300 && mp.x <= 500 && mp.y >= 300 && mp.y <= 360) {
                m_buttonPressed = true;
            }
        }
    }
}

void StartScene::update() {
    if (m_buttonPressed && m_manager) {
        // 切换到剧情场景（StoryScene 需在项目中添加）
        // 为避免循环依赖，这里只展示用法：用户可替换为 StoryScene 的实际构造函数
        // m_manager->changeScene(std::make_unique<StoryScene>(m_manager, ...));
        m_buttonPressed = false;
    }
}

void StartScene::render() {
    cleardevice();
    // 背景占位
    setfillcolor(RGB(30, 30, 40));
    solidrectangle(0, 0, getwidth(), getheight());

    // 绘制标题
    settextstyle(40, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(220, 120, _T("MazeGame - 迷宫冒险"));

    // 绘制开始按钮
    setfillcolor(RGB(70, 130, 180));
    solidrectangle(300, 300, 500, 360);
    settextstyle(28, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(350, 318, _T("开始游戏"));
}