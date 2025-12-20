#pragma once
#include <memory>
#include "scene/Scene.h"

class SceneManager {
private:
    std::unique_ptr<Scene> m_current;

public:
    SceneManager() = default;
    ~SceneManager() = default;

    void changeScene(std::unique_ptr<Scene> scene) {
        if (m_current) m_current->onExit();
        m_current = std::move(scene);
        if (m_current) { m_current->onEnter(); m_current->init(); }
    }

    void processInput() {
        if (m_current) m_current->processInput();
    }

    void update() {
        if (m_current) m_current->update();
    }

    void render() {
        if (m_current) m_current->render();
    }
};