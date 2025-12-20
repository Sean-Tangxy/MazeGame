#pragma once
#include <string>

class AudioManager {
public:
    static void playMusic(const std::string& path, bool loop = true);
    static void stopMusic();
    static void playEffect(const std::string& path);
};