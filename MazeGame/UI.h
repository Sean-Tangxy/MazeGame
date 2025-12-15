// UI.h
#pragma once
#include <string>
#include <graphics.h>

class UI {
private:
    IMAGE startScreen;
    IMAGE buttonImage;

public:
    UI();
    ~UI();

    void renderStartScreen();
    void renderHUD(int score, int health, bool hasKey);
    void renderGameOver(int score);
    void renderWinScreen(int score);
    void renderButton(int x, int y, const std::string& text, bool hovered = false);

    bool isStartButtonClicked(int mouseX, int mouseY);
};