// GameObject.h
#pragma once
#include <graphics.h>
#include <string>
#include <memory>

//
// 兼容性适配：EasyX 在不同版本中对 getwidth/getheight 的接口可能不同。
// 项目中大量调用形如 getwidth(&sprite) / getheight(&sprite)。
// 若库提供的是成员函数 IMAGE::getwidth() / IMAGE::getheight()（无参数），
// 则下面提供的全局内联重载可以接收 IMAGE* / const IMAGE*，并转发到成员函数，
// 从而修复 “E0140: 函数调用中的参数太多” 的编译错误。
// 放在包含 EasyX 头之后以确保 `IMAGE` 类型已知。
//
inline int getwidth(const IMAGE* img) {
    return img ? img->getwidth() : 0;
}
inline int getwidth(IMAGE* img) {
    return getwidth(static_cast<const IMAGE*>(img));
}
inline int getheight(const IMAGE* img) {
    return img ? img->getheight() : 0;
}
inline int getheight(IMAGE* img) {
    return getheight(static_cast<const IMAGE*>(img));
}
//

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class GameObject {
protected:
    Position position;
    int width;
    int height;
    IMAGE sprite;
    bool visible;
    std::string tag;  // 用于标识对象类型

public:
    GameObject(int x = 0, int y = 0, int w = 32, int h = 32);
    virtual ~GameObject();

    virtual void update() = 0;
    virtual void render();
    virtual void onCollision(GameObject* other);

    // Getter/Setter
    Position getPosition() const;
    void setPosition(int x, int y);
    int getWidth() const;
    int getHeight() const;
    std::string getTag() const;
    bool isVisible() const;
    void setVisible(bool v);

    // 碰撞检测
    bool checkCollision(const GameObject* other) const;
    bool checkCollision(int x, int y, int w, int h) const;

    // 加载图片
    bool loadImage(const std::string& filename);
};