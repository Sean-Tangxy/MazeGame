#include <windows.h>
#include <graphics.h>
#include "../include/scene/TutorialScene.h"

TutorialScene::TutorialScene()
    : m_loaded(false),
      m_lastTick(0) {
}

TutorialScene::~TutorialScene() {
    onExit();
}

void TutorialScene::init() {
    // 可在此加载资源或初始化状态
}

void TutorialScene::onEnter() {
    m_loaded = true;
    m_lastTick = GetTickCount64();
    // 如果需要播放 BGM 或重置界面状态可在这里处理
}

void TutorialScene::onExit() {
    m_loaded = false;
    // 释放资源（若有）
}

void TutorialScene::processInput() {
    // 处理即时输入（可以保留空实现）
}

void TutorialScene::update() {
    if (!m_loaded) return;

    // 简单示例：按 空格 / 回车 或 单击 可切换到下一场景
    // 实际切换目标由项目需求决定，这里注释示例以避免未定义依赖
    /*
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)) {
        extern SceneManager* g_sceneManager;
        g_sceneManager->changeScene(std::make_unique<SomeNextScene>());
    }
    while (MouseHit()) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            extern SceneManager* g_sceneManager;
            g_sceneManager->changeScene(std::make_unique<SomeNextScene>());
        }
    }
    */
}

void TutorialScene::render() {
    if (!m_loaded) return;

    // 使用 EasyX 做一个简单占位渲染
    cleardevice();
    settextstyle(30, 0, "微软雅黑");
    settextcolor(WHITE);
    const char* title = "教程界面（示例）";
    int x = (getwidth() - textwidth(title)) / 2;
    int y = getheight() / 3;
    outtextxy(x, y, title);

    settextstyle(18, 0, "微软雅黑");
    const char* tip = "按 空格 / 回车 或 单击 继续（在 update 中实现切换）";
    int tx = (getwidth() - textwidth(tip)) / 2;
    outtextxy(tx, y + 80, tip);
}