// Game.cpp - 完整实现
#include "Game.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <Windows.h> // 为 GetAsyncKeyState, GetCursorPos, ScreenToClient 等 WinAPI 提供声明

Game::Game() : score(0), playerHealth(100), hasKey(false),
currentMap(nullptr), player(nullptr), enemy(nullptr),
items(nullptr), ui(nullptr) {
    // 初始化图形窗口
    initgraph(800, 600);
    setbkcolor(RGB(50, 50, 70)); // 设置背景色
    cleardevice();

    // 初始化游戏
    initGame();
}

Game::~Game() {
    cleanup();
}

void Game::cleanup() {
    if (currentMap) { delete currentMap; currentMap = nullptr; }
    if (player)     { delete player;     player = nullptr; }
    if (enemy)      { delete enemy;      enemy = nullptr; }
    if (items)      { delete items;      items = nullptr; }
    if (ui)         { delete ui;         ui = nullptr; }
}

void Game::loadResources() {
    // 当前项目资源的简单占位实现。
    // 如果需要预加载图片/音效/配置可以在这里实现。
    // 保留为空实现以避免链接错误并提供未来扩展点。
    // 例如：ui->loadImages(); currentMap->loadTiles(); 等。
}

void Game::initGame() {
    // 清空现有资源
    cleanup();

    // 重置游戏状态
    score = 0;
    playerHealth = 100;
    hasKey = false;

    // 创建新游戏对象
    currentMap = new Map("resources/maps/level1.txt");
    player = new Player(50, 50);
    enemy = new Enemy(400, 300);
    items = new ItemManager();
    ui = new UI();

    // 预加载/初始化资源（如果有）
    loadResources();

    // 初始化物品
    items->initLevel();

    // 设置初始状态
    state = GAME_START;
}

void Game::processInput() {
    // 检查ESC键退出
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        // 在退出前清理资源并结束绘制
        cleanup();
        // 结束图形库（如果需要，可根据使用的图形库添加相应清理函数）
        exit(0);
    }

    // 检查鼠标点击
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
        // 获取鼠标位置
        POINT mousePos;
        if (GetCursorPos(&mousePos)) {
            // 将屏幕坐标转换为窗口客户区坐标
            ScreenToClient(GetHWnd(), &mousePos);

            if (state == GAME_START) {
                if (ui && ui->isStartButtonClicked(mousePos.x, mousePos.y)) {
                    state = GAME_PLAYING;
                    Sleep(200); // 防止连续点击
                }
            }
            else if (state == GAME_OVER || state == GAME_WIN) {
                // 检查重新开始按钮
                if (mousePos.x >= 300 && mousePos.x <= 500 &&
                    mousePos.y >= 350 && mousePos.y <= 410) {
                    initGame();
                    state = GAME_PLAYING;
                    Sleep(200);
                }
                // 检查退出按钮
                else if (mousePos.x >= 300 && mousePos.x <= 500 &&
                    mousePos.y >= 420 && mousePos.y <= 480) {
                    cleanup();
                    exit(0);
                }
            }
        }
    }
}

void Game::update() {
    if (state != GAME_PLAYING) return;

    // 更新玩家
    if (player) player->update();

    // 更新敌人
    if (enemy) enemy->update();

    // 敌人追逐玩家
    if (enemy && player) {
        Position pos = player->getPosition();
        enemy->chase(std::make_pair(pos.x, pos.y));
    }

    // 更新物品
    if (items) items->update();

    // 检查碰撞
    checkCollisions();

    // 检查游戏结束条件
    if (player && player->getHealth() <= 0) {
        state = GAME_OVER;
    }
}

void Game::checkCollisions() {
    if (!player || !currentMap || !enemy || !items) return;

    // 检查玩家与墙壁的碰撞
    if (currentMap->isWall(player->getPosition().x, player->getPosition().y)) {
        // 简单处理：将玩家推回
        player->setPosition(player->getPosition().x - 5, player->getPosition().y - 5);
    }

    // 检查玩家与物品的碰撞
    items->checkCollisions(player);

    // 检查玩家与敌人的碰撞
    if (player->checkCollision(enemy)) {
        player->takeDamage(10);
        // 将玩家和敌人弹开
        Position playerPos = player->getPosition();
        Position enemyPos = enemy->getPosition();

        int dx = playerPos.x - enemyPos.x;
        int dy = playerPos.y - enemyPos.y;

        player->setPosition(playerPos.x + dx / 2, playerPos.y + dy / 2);
        enemy->setPosition(enemyPos.x - dx / 2, enemyPos.y - dy / 2);
    }

    // 更新UI状态
    playerHealth = player->getHealth();
    hasKey = items->hasKeyBeenCollected();

    // 如果拿到钥匙，解锁出口
    if (hasKey) {
        // 在实际游戏中，这里应该解锁出口
    }
}

void Game::render() {
    // 清空屏幕
    cleardevice();

    switch (state) {
    case GAME_START:
        if (ui) ui->renderStartScreen();
        break;

    case GAME_PLAYING:
        if (currentMap) currentMap->render();
        if (player) player->render();
        if (enemy) enemy->render();
        if (items) items->render();
        if (ui) ui->renderHUD(score, playerHealth, hasKey);
        break;

    case GAME_OVER:
        if (currentMap) currentMap->render();
        if (player) player->render();
        if (enemy) enemy->render();
        if (items) items->render();
        if (ui) {
            ui->renderHUD(score, playerHealth, hasKey);
            ui->renderGameOver(score);
        }
        break;

    case GAME_WIN:
        if (currentMap) currentMap->render();
        if (player) player->render();
        if (enemy) enemy->render();
        if (items) items->render();
        if (ui) {
            ui->renderHUD(score, playerHealth, hasKey);
            ui->renderWinScreen(score);
        }
        break;
    }

    // 显示渲染结果
    FlushBatchDraw();
}

void Game::run() {
    // 启用批量绘制，提高渲染效率
    BeginBatchDraw();

    // 游戏主循环
    while (true) {
        processInput();
        update();
        render();

        // 控制帧率 (约60FPS)
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    // 如果未来修改为可退出循环，应确保 EndBatchDraw 被调用。
    EndBatchDraw();
}