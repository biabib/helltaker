#ifndef ANIMATED_CHARACTER_HPP
#define ANIMATED_CHARACTER_HPP

#include <vector>
#include <string>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Map.hpp"


class AnimatedCharacter : public Util::GameObject {

public:
    explicit AnimatedCharacter(const std::vector<std::string>& AnimationPaths);

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
        temp->Play();
    }

    void Pause(){
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->Pause();
    }

    void SetCurrentFrame(){
        auto temp = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        temp->SetCurrentFrame(0);
    }

    [[nodiscard]] bool IfAnimationEnds() const;
    AnimatedCharacter(const AnimatedCharacter&) = delete;

    AnimatedCharacter(AnimatedCharacter&&) = delete;

    AnimatedCharacter& operator=(const AnimatedCharacter&) = delete;

    AnimatedCharacter& operator=(AnimatedCharacter&&) = delete;

    [[nodiscard]] const std::string& GetImagePath() const { return m_ImagePath; }

    [[nodiscard]] const glm::vec2& GetPosition() const { return m_Transform.translation; }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }
    void Move(int dx, int dy, int maxCols, int maxRows);

    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }

private:
    void ResetPosition() { m_Transform.translation = {0, 0}; }
    std::string m_ImagePath;
};


#endif //ANIMATED_CHARACTER_HPP
