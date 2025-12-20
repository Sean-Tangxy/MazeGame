#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <memory> // 为 std::make_unique 和 unique_ptr 引入
#include "../include/scene/StoryScene.h"
#include "../include/component/SceneManager.h"
#include "../include/scene/TutorialScene.h" // 添加这一行，确保能找到 TutorialScene 的声明
#include <graphics.h>

StoryScene::StoryScene()
    : m_currentIndex(0),
      m_displayMs(4500), // 每张 CG 显示约 4.5 秒（含过渡）
      m_elapsedMs(0),
      m_loaded(false),
      m_lastTick(0),
      m_showFinalTextOnly(false) {
    // 按顺序列出 CG 路径
    m_imagePaths = {
        "resources/images/cg01",
        "resources/images/cg02",
        "resources/images/cg03",
        "resources/images/cg04"
    };

    // 对应字幕（第5条为结语，单独显示在最后）
    m_subtitles = {
        "在南极澄澈的苍穹下，小企鹅与族群一直过着平静而欢腾的生活。冰川环绕，极光如梦，它们每日在晶莹的雪原上追逐、在蔚蓝的海水中嬉戏，仿佛这片纯白净土会永远守护着它们的欢笑。",
        "直到某一日，天空飘下了陌生的灰雪。",
        "那雪色泽黯淡，触之即融，却带着一丝不属于冰雪的气息。起初谁也没有在意，可不久后，小企鹅眼睁睁看着身边的同伴一个接一个无力地倒下。皑皑白雪之上，那些曾经活跃的身影变得寂静，唯有灰雪无声覆盖。",
        "（1）焦急的小企鹅奔向族群中最年长的企鹅长老。长老仰望着不再湛蓝的天空，沉重地告诉它：那是远方人类工厂排放的污秽之物，是吞噬生命的“灰雪”。若放任不管，整个族群将无人幸免。\n（2）望向倒下的同伴与长老忧虑的目光，小企鹅心中涌起一股前所未有的决心。它用鳍轻轻拍了拍胸前的积雪，转身面向灰雪飘来的远方——"
    };
}

StoryScene::~StoryScene() {
    onExit();
}

void StoryScene::onEnter() {
    m_images.clear();
    // 预加载图片
    for (const auto &p : m_imagePaths) {
        IMAGE img;
        // loadimage 返回值在不同 EasyX 版本可能不同，直接尝试加载
        loadimage(&img, p.c_str());
        m_images.push_back(img);
    }
    m_loaded = true;
    m_currentIndex = 0;
    m_elapsedMs = 0;
    m_lastTick = GetTickCount64();
    m_showFinalTextOnly = false;

    // 可在此播放剧情 BGM（若实现了 AudioManager）
    // AudioManager::getInstance()->playMusic("Assets/Audio/Music/StoryTheme.ogg");
}

void StoryScene::onExit() {
    m_loaded = false;
    m_images.clear();
}

void StoryScene::update() {
    if (!m_loaded) return;

    unsigned long long now = GetTickCount64();
    int delta = static_cast<int>(now - m_lastTick);
    m_lastTick = now;
    m_elapsedMs += delta;

    // 支持鼠标/键盘快进：按下则直接跳到下一张
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)) {
        m_elapsedMs = m_displayMs;
    }
    while (MouseHit()) {
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            m_elapsedMs = m_displayMs;
        }
    }

    if (!m_showFinalTextOnly) {
        if (m_elapsedMs >= m_displayMs) {
            m_elapsedMs = 0;
            m_currentIndex++;
            if (m_currentIndex >= static_cast<int>(m_images.size())) {
                // 播放完 4 张 CG，显示第 5 条结语文本页
                m_showFinalTextOnly = true;
                m_elapsedMs = 0;
            }
        }
    }
    else {
        // 在第五条文字页，按任意键或点击进入 TutorialScene
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)) {
            // 你需要有一个 SceneManager 实例，假设有全局指针 g_sceneManager
            extern SceneManager* g_sceneManager;
            g_sceneManager->changeScene(std::make_unique<TutorialScene>());
        }
        while (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                // 你需要有一个 SceneManager 实例，假设有全局指针 g_sceneManager
                extern SceneManager* g_sceneManager;
                g_sceneManager->changeScene(std::make_unique<TutorialScene>());
            }
        }
    }
}

void StoryScene::render() {
    if (!m_loaded) return;

    int screenW = 1280;
    int screenH = 720;
    // 尝试使用第一张图片的分辨率作为画布大小
    if (!m_images.empty()) {
        screenW = m_images[0].getwidth();
        screenH = m_images[0].getheight();
    }

    if (!m_showFinalTextOnly) {
        if (m_currentIndex >= 0 && m_currentIndex < static_cast<int>(m_images.size())) {
            // 绘制当前 CG（拉伸以填屏）
            putimage(0, 0, &m_images[m_currentIndex]);

            // 简单“淡出”过渡：当接近切换时间的最后 250ms 时，绘制一层黑色渐变覆盖以模拟淡出
            if (m_elapsedMs > m_displayMs - 250) {
                int remain = m_displayMs - m_elapsedMs; // 0..250
                int alphaStep = (250 - remain); // 0..250
                // 使用若干步的固色覆盖模拟渐变（EasyX 无 alpha 时使用灰度覆盖）
                int cover = (alphaStep * 200) / 250; // 0..200 黑度
                setfillcolor(RGB(cover, cover, cover));
                setbkcolor(RGB(cover, cover, cover));
                solidrectangle(0, 0, screenW, screenH);
            }

            // 绘制字幕（白色），底部居中，带黑色底框凸显
            int subIndex = std::min(m_currentIndex, static_cast<int>(m_subtitles.size() - 1));
            std::string sub = m_subtitles[subIndex];

            // 字体与颜色
            settextstyle(26, 0, "微软雅黑");
            settextcolor(WHITE);

            // 文本多行处理：按行分割 '\n'
            std::vector<std::string> lines;
            size_t pos = 0;
            while (pos < sub.size()) {
                size_t nl = sub.find('\n', pos);
                if (nl == std::string::npos) nl = sub.size();
                lines.push_back(sub.substr(pos, nl - pos));
                pos = nl + 1;
            }

            // 计算文本块尺寸（简单按最长行宽）
            int maxW = 0;
            int lineH = textheight("A");
            for (const auto &ln : lines) {
                int w = textwidth(ln.c_str());
                if (w > maxW) maxW = w;
            }
            int padding = 20;
            int boxW = maxW + padding * 2;
            int boxH = static_cast<int>(lines.size()) * lineH + padding * 2;
            int boxX = (screenW - boxW) / 2;
            int boxY = screenH - boxH - 60;

            // 绘制黑色背景（不透明，用于凸显）
            setfillcolor(BLACK);
            solidrectangle(boxX, boxY, boxX + boxW, boxY + boxH);

            // 绘制每行文本（白色）
            settextcolor(WHITE);
            for (size_t i = 0; i < lines.size(); ++i) {
                int tx = boxX + padding;
                int ty = boxY + padding + static_cast<int>(i) * lineH;
                outtextxy(tx, ty, lines[i].c_str());
            }
        }
    }
    else {
        // 第五条结语文本页（纯文本，居中显示）
        putimage(0, 0, &m_images.back()); // 仍然显示最后一张图作为背景（若存在）
        // 顶部/中部显示结语
        std::string finale = "一场为了拯救家园与挚友的远征，就此开始。";
        settextstyle(36, 0, "微软雅黑");
        settextcolor(WHITE);

        // 黑色半透明条（模拟）作为背景
        int tw = textwidth(finale.c_str());
        int th = textheight(finale.c_str());
        int bx = (screenW - tw) / 2 - 30;
        int by = (screenH - th) / 2 - 20;
        setfillcolor(BLACK);
        solidrectangle(bx, by, bx + tw + 60, by + th + 40);
        outtextxy(bx + 30, by + 20, finale.c_str());

        // 底部提示
        const char* tip = "按 空格 / 回车 或 单击 继续";
        settextstyle(20, 0, "微软雅黑");
        settextcolor(RGB(200, 200, 200));
        int tx = (screenW - textwidth(tip)) / 2;
        outtextxy(tx, by + th + 80, tip);
    }
}

void StoryScene::init() {
    // 场景初始化，当前无需额外操作（保留空实现以满足抽象基类要求）
}

void StoryScene::processInput() {
    // 单独的输入处理（如果需要将 input 从 update 分离，可在此实现）
    // 当前逻辑已在 update 中处理快进/点击，故此处保持空实现
}