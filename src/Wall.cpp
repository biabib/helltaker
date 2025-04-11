//
// Created by USER on 2025/4/11.
//
#include "Wall.hpp"

Wall::Wall(float x, float y, const std::string& texturePath)
        : m_TexturePath(texturePath) {
    m_Drawable = std::make_shared<Util::Image>(texturePath);
    SetPosition({x, y});
}