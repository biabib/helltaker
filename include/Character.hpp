#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

#include "Util/GameObject.hpp"

class Character : public Util::GameObject {
public:
    explicit Character(const std::string& ImagePath);

    Character(const Character&) = delete;

    Character(Character&&) = delete;

    Character& operator=(const Character&) = delete;

    Character& operator=(Character&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string& ImagePath);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    [[nodiscard]] bool IfCollides(const std::shared_ptr<Character>& other) const {
        auto thisPosition = this->GetPosition();
        auto thisZIndex = this->GetZIndex();
        auto otherPosition = other->GetPosition();
        auto otherZIndex = other->GetZIndex();

        return (thisPosition.x + thisZIndex >= otherPosition.x && thisPosition.x - thisZIndex <= otherPosition.x) &&
               (thisPosition.y + thisZIndex >= otherPosition.y && thisPosition.y - thisZIndex <= otherPosition.y);
    }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};


#endif //CHARACTER_HPP
