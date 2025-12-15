// Game.h
#pragma once
#include <graphics.h>
#include "GameState.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "ItemManager.h"
#include "UI.h"

class Game {
private:
    GameState state;
    Map* currentMap;
    Player* player;
    Enemy* enemy;
    ItemManager* items;
    UI* ui;

    int score;
    int playerHealth;
    bool hasKey;

    void initGame();
    void update();
    void render();
    void processInput();
    void checkCollisions();
    void loadResources();
	void cleanup();

public:
    Game();
    ~Game();
    void run();
};