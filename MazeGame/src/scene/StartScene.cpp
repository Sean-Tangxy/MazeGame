#include <windows.h>
#include <iostream>
#include <memory> // 为 std::make_unique 引入
#include "../include/scene/StartScene.h"
#include "../include/component/SceneManager.h"
#include "../include/scene/StoryScene.h"
#include <graphics.h>

StartScene::StartScene()
    : m_btnLoaded(false),
    m_btnX(810), m_btnY(560), m_btnW(300), m_btnH(80),
    m_resourcesLoaded(false) {
}

StartScene::~StartScene() {
    onExit();
}

void StartScene::onEnter() {
    // 载入资源（请将资源放在 Assets/ 对应目录）
    if (loadimage(&m_background, "resources/images/background01") != 0) {
        // loadimage 返回非 0 可能表示失败，按项目 EasyX 版本调整检查
    }
    if (loadimage(&m_btnStart, "Assets/UI/Buttons/btn_start.png", m_btnW, m_btnH) == 0) {
        m_btnLoaded = true;
    }
    m_resourcesLoaded = true;

    // 设置鼠标可见（若需要）
    // ShowCursor(TRUE);
}

void StartScene::onExit() {
    m_resourcesLoaded = false;
    m_btnLoaded = false;
    // EasyX 不需要显式释放 IMAGE，但清空标志以便重新加载
}

void StartScene::update() {
    if (!m_resourcesLoaded) return;

    // 处理鼠标点击：若点击开始按钮，进入剧情场景
    while (MouseHit()) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            int mx = msg.x;
            int my = msg.y;
            if (mx >= m_btnX && mx <= m_btnX + m_btnW && my >= m_btnY && my <= m_btnY + m_btnH) {
                // 切换到 StoryScene，使用全局指针 g_sceneManager
                extern SceneManager* g_sceneManager;
                if (g_sceneManager) {
                    g_sceneManager->changeScene(std::make_unique<StoryScene>());
                }
                return;
            }
        }
    }

    // 支持 Enter/Space 快速开始
    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000)) {
        extern SceneManager* g_sceneManager;
        if (g_sceneManager) {
            g_sceneManager->changeScene(std::make_unique<StoryScene>());
        }
    }
}

void StartScene::render() {
    if (!m_resourcesLoaded) return;

    // 背景拉满屏
    putimage(0, 0, &m_background);

    // 标题：居中，微软雅黑，深蓝色，加粗（通过较大字号模拟加粗）
    const char* title = "灰色的雪";
    // 设置字体（高度 80，根据屏幕分辨率调整）
    settextstyle(80, 0, "微软雅黑");
    settextcolor(RGB(0, 30, 90)); // 深蓝色
    int titleW = textwidth(title);
    int titleX = (getwidth() - titleW) / 2;
    int titleY = 200;
    outtextxy(titleX, titleY, title);

    // 按钮：优先使用图片，否则绘制简易矩形按钮
    if (m_btnLoaded) {
        putimage(m_btnX, m_btnY, &m_btnStart);
        // 按钮文字（置于图片上方，较小）
        const char* btnText = "开始游戏";
        settextstyle(28, 0, "微软雅黑");
        settextcolor(WHITE);
        int tw = textwidth(btnText);
        int tx = m_btnX + (m_btnW - tw) / 2;
        int ty = m_btnY + (m_btnH - textheight(btnText)) / 2;
        outtextxy(tx, ty, btnText);
    }
    else {
        // 绘制灰色按钮背景与蓝色边框
        setfillcolor(RGB(230, 230, 230));
        solidrectangle(m_btnX, m_btnY, m_btnX + m_btnW, m_btnY + m_btnH);
        setlinecolor(RGB(0, 30, 90));
        rectangle(m_btnX, m_btnY, m_btnX + m_btnW, m_btnY + m_btnH);
        const char* btnText = "开始游戏";
        settextstyle(28, 0, "微软雅黑");
        settextcolor(RGB(0, 30, 90));
        int tw = textwidth(btnText);
        int tx = m_btnX + (m_btnW - tw) / 2;
        int ty = m_btnY + (m_btnH - textheight(btnText)) / 2;
        outtextxy(tx, ty, btnText);
    }
}