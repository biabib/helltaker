//
// Created by USER on 2025/3/28.
//
#include "Box.hpp"

Box::Box(float x, float y, const std::string& texturePath)
        : m_TexturePath(texturePath) {
    m_Drawable = std::make_shared<Util::Image>(texturePath);
    SetPosition({x, y});
}

void Box::Move(float dx, float dy) {
    auto Position = this ->GetPosition();
    Position.x += dx;
    Position.y += dy;
    SetPosition(Position);
}