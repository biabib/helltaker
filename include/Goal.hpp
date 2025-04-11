//
// Created by USER on 2025/4/11.
//

#ifndef HELLTAKER_GOAL_HPP
#define HELLTAKER_GOAL_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Map.hpp"

class Goal : public Util::GameObject {
public:
    explicit Goal(const std::vector<std::string>& AnimationPaths);

    [[nodiscard]] bool IsLooping() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
    }

    [[nodiscard]] bool IsPlaying() const {
        return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() == Util::Animation::State::PLAY;
    }

    void SetLooping(bool looping) {
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetLooping(looping);
    }

    void SetAnimation(const std::vector<std::string>& AnimationPaths, bool loop = true) {
        m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, loop, 60, false, 0);
    }

    [[nodiscard]] bool IfAnimationEnds() const;


    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }


    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};

#endif //HELLTAKER_GOAL_HPP
