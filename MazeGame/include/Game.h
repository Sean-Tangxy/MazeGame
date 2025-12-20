// Game.h
#pragma once
#include <graphics.h>
#include "GameState.h"
#include "object/Map.h"
#include "object/Player.h"
#include "object/Enemy.h"
#include "component/ItemManager.h"
#include "component/UI.h"

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