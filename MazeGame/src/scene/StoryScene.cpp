#include "scene/StoryScene.h"
#include <Windows.h>

StoryScene::StoryScene(SceneManager* mgr, const std::vector<std::string>& imgs)
    : m_manager(mgr), m_images(imgs), m_index(0) {
}

void StoryScene::init() {
    // 预加载图片可在此实现
}

void StoryScene::onEnter() {
    // 播放剧情音乐
    AudioManager::playMusic("Assets/music/story.wav", true);
}

void StoryScene::onExit() {
    AudioManager::stopMusic();
}

void StoryScene::processInput() {
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        POINT mp;
        if (GetCursorPos(&mp)) {
            ScreenToClient(GetHWnd(), &mp);
            // 点击任意位置翻页
            m_index++;
            Sleep(150); // 防止连点
        }
    }
}

void StoryScene::update() {
    // 超出图片数量后切换到下一逻辑（例如 PlayScene 或 Tutorial）
    if (m_index >= m_images.size()) {
        // m_manager->changeScene(std::make_unique<PlayScene>(m_manager));
        m_index = m_images.size() - 1;
    }
}

void StoryScene::render() {
    cleardevice();
    setfillcolor(RGB(10, 10, 20));
    solidrectangle(0, 0, getwidth(), getheight());

    // 渲染占位文字/图片索引
    settextstyle(24, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    char buf[64];
    sprintf_s(buf, "剧情页 %zu / %zu", m_index + 1, m_images.size());
    outtextxy(20, 20, buf);
    // 实际工程中在此用 putimage 显示 m_images[m_index]
}