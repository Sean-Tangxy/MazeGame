#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "../include/component/AudioManager.h"

void AudioManager::playMusic(const std::string& path, bool loop) {
    if (path.empty()) return;
    UINT flags = SND_FILENAME | SND_ASYNC;
    if (loop) flags |= SND_LOOP;
    PlaySoundA(path.c_str(), NULL, flags);
}

void AudioManager::stopMusic() {
    PlaySoundA(NULL, NULL, 0);
}

void AudioManager::playEffect(const std::string& path) {
    if (path.empty()) return;
    PlaySoundA(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}