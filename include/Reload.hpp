//
// Created by USER on 2025/5/2.
//

#ifndef HELLTAKER_RELOAD_HPP
#define HELLTAKER_RELOAD_HPP


#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Map.hpp"


class Reload : public Util::GameObject {

public:
    explicit Reload(const std::vector<std::string>& AnimationPaths);

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

    void Play(){
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetCurrentFrame(0);  // 重設到第一幀
        temp->Play();              // 播放動畫
    }

    void Pause(){
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Pause();
    }

    [[nodiscard]] bool IfAnimationEnds() const;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

    // TODO: Implement the collision detection


    // TODO: Add and implement more methods and properties as needed to finish Giraffe Adventure.

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }

    std::string m_ImagePath;
};


#endif //HELLTAKER_RELOAD_HPP
