//
// Created by USER on 2025/3/28.
//

#ifndef HELLTAKER_BOX_HPP
#define HELLTAKER_BOX_HPP

#include "Util/GameObject.hpp"
#include "Map.hpp"

class Box : public Util::GameObject {
public:
    explicit Box(float x, float y, const std::string& texturePath);

    void Move(float dx, float dy);

    [[nodiscard]] glm::vec2 GetPosition() const { return m_Transform.translation; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }


private:

    std::string m_TexturePath;
};
#endif //HELLTAKER_BOX_HPP
