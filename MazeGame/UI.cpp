// UI.cpp
#include "UI.h"
#include <string>
#include <sstream>

UI::UI() {
    // 加载开始界面图片
    loadimage(&startScreen, _T("resources/images/start_bg.png"), 800, 600);

    // 加载按钮图片
    loadimage(&buttonImage, _T("resources/images/button.png"), 200, 60);
}

UI::~UI() {
}

void UI::renderStartScreen() {
    // 绘制开始界面背景
    putimage(0, 0, &startScreen);

    // 绘制游戏标题
    settextcolor(YELLOW);
    settextstyle(48, 0, _T("黑体"));
    outtextxy(250, 100, _T("迷宫冒险"));

    // 绘制开始按钮
    renderButton(300, 300, "开始游戏");

    // 绘制游戏说明
    settextcolor(WHITE);
    settextstyle(18, 0, _T("宋体"));
    outtextxy(200, 400, _T("游戏目标: 收集所有金币和钥匙，然后到达出口"));
    outtextxy(200, 430, _T("控制方式: W/A/S/D 移动，避开敌人"));
    outtextxy(200, 460, _T("注意: 必须拿到钥匙才能打开出口"));
}

void UI::renderHUD(int score, int health, bool hasKey) {
    // 绘制分数
    settextcolor(WHITE);
    settextstyle(24, 0, _T("宋体"));

    std::stringstream ss;
    ss << "分数: " << score;
    outtextxy(10, 10, ss.str().c_str());

    // 绘制生命值
    ss.str("");
    ss << "生命: " << health;
    outtextxy(10, 40, ss.str().c_str());

    // 绘制钥匙状态
    if (hasKey) {
        settextcolor(GREEN);
        outtextxy(10, 70, _T("钥匙: 已获得"));
    }
    else {
        settextcolor(RED);
        outtextxy(10, 70, _T("钥匙: 未获得"));
    }

    // 绘制操作提示
    settextcolor(WHITE);
    settextstyle(14, 0, _T("宋体"));
    outtextxy(600, 10, _T("W/A/S/D: 移动"));
    outtextxy(600, 30, _T("ESC: 退出游戏"));
}

void UI::renderGameOver(int score) {
    // 绘制半透明黑色背景
    setfillcolor(BLACK);
    solidrectangle(200, 150, 600, 450);

    // 绘制游戏结束文本
    settextcolor(RED);
    settextstyle(48, 0, _T("黑体"));
    outtextxy(280, 200, _T("游戏结束"));

    // 绘制分数
    settextcolor(WHITE);
    settextstyle(24, 0, _T("宋体"));

    std::stringstream ss;
    ss << "最终分数: " << score;
    outtextxy(300, 280, ss.str().c_str());

    // 绘制重新开始按钮
    renderButton(300, 350, "重新开始");

    // 绘制退出按钮
    renderButton(300, 420, "退出游戏");
}

void UI::renderWinScreen(int score) {
    // 绘制半透明黑色背景
    setfillcolor(BLACK);
    solidrectangle(200, 150, 600, 450);

    // 绘制胜利文本
    settextcolor(YELLOW);
    settextstyle(48, 0, _T("黑体"));
    outtextxy(280, 200, _T("恭喜通关!"));

    // 绘制分数
    settextcolor(WHITE);
    settextstyle(24, 0, _T("宋体"));

    std::stringstream ss;
    ss << "最终分数: " << score;
    outtextxy(300, 280, ss.str().c_str());

    // 绘制重新开始按钮
    renderButton(300, 350, "重新开始");

    // 绘制退出按钮
    renderButton(300, 420, "退出游戏");
}

void UI::renderButton(int x, int y, const std::string& text, bool hovered) {
    // 绘制按钮背景
    if (buttonImage.getwidth() > 0) {
        putimage(x, y, &buttonImage);
    }
    else {
        // 使用默认按钮样式
        if (hovered) {
            setfillcolor(RGB(100, 150, 200));
        }
        else {
            setfillcolor(RGB(70, 120, 170));
        }
        fillrectangle(x, y, x + 200, y + 60);

        // 绘制按钮边框
        setlinecolor(WHITE);
        rectangle(x, y, x + 200, y + 60);
    }

    // 绘制按钮文字
    settextcolor(WHITE);
    settextstyle(24, 0, _T("宋体"));
    setbkmode(TRANSPARENT);

    // 计算文字居中位置
    int textWidth = text.length() * 12; // 估算宽度
    int textX = x + (200 - textWidth) / 2;
    int textY = y + 18;

    outtextxy(textX, textY, text.c_str());
}

bool UI::isStartButtonClicked(int mouseX, int mouseY) {
    // 检查是否点击了开始按钮 (位置: 300, 300, 大小: 200x60)
    return mouseX >= 300 && mouseX <= 500 && mouseY >= 300 && mouseY <= 360;
}