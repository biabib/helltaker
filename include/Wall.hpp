//
// Created by USER on 2025/4/11.
//

#ifndef HELLTAKER_WALL_HPP
#define HELLTAKER_WALL_HPP
#include "Util/GameObject.hpp"
#include "Map.hpp"

class Wall : public Util::GameObject {
public:
    explicit Wall(float x, float y, const std::string& texturePath);

    [[nodiscard]] glm::vec2 GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }


private:
    std::string m_TexturePath;
};


#endif //HELLTAKER_WALL_HPP
