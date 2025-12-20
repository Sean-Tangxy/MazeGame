#pragma once
#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <cassert>
#include <random>
#include <string>

#ifdef __APPLE__
static const std::string ASSET_DIR = "../../resources/images/";
#else
static const std::string ASSET_DIR = "../resources/images/";
#endif // __APPLE__

// Returns a random integer within [min, max] (inclusive).
inline int randInt(int min, int max) {
    if (max < min)
        std::swap(max, min);
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

enum class LevelStatus { ONGOING, LOSING };

enum class KeyCode {
    NONE,
    ENTER, // Enter
    QUIT   // Esc
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum class ImageID {
    NONE = 0,
    START_BUTTOM,
    BACKGROUND_START,
    BACKGROUND_LEVEL_1,
    BACKGROUND_LEVEL_2,
    BACKGROUND_LEVEL_3,
    BACKGROUND_LEVEL_4,

    FLOOR = 10,
    WALL,
    EXIT,

    COIN = 20,
    KEY,
    POTION,

    CHARACTER = 30,
    ENERMY,
};

enum class AnimID { NO_ANIMATION = 0 };

const int MAX_LAYERS = 5;

enum class LayerID {
    CHARACTER = 0,
    TOOLS,
    MAP,
    UI,
    BACKGROUND,
};

const int MS_PER_FRAME = 33;

#endif // !UTILS_HPP__
