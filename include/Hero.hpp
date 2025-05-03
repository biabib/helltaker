//
// Created by USER on 2025/5/4.
//

#ifndef HELLTAKER_HERO_HPP
#define HELLTAKER_HERO_HPP

#include "Util/GameObject.hpp"
#include "App.hpp"
#include "Box.hpp"
#include "Enemy.hpp"
#include "Util/Keycode.hpp"

class Hero : public Util::GameObject {
public:
    Hero(App& app);

    void Move(const glm::vec2& direction, bool& isPushingBox, bool& isPushingEnemy, bool& canPush);
    bool IsAtPosition(const glm::vec2& position);
    void SetAnimation(const std::vector<std::shared_ptr<Util::Image>>& animationImages, bool loop = false);
    bool IfAnimationEnds() const;

    bool IsBoxAtPosition(const glm::vec2& position, std::shared_ptr<Box>& outBox);
    bool IsEnemyAtPosition(const glm::vec2& position, std::shared_ptr<Enemy>& outEnemy);
    bool IsGoalAtPosition(const glm::vec2& position);
    bool IsWalkable(const glm::vec2 &position);

    void SetHasKey(bool hasKey) { m_HasKey = hasKey; }
    bool GetHasKey() const { return m_HasKey; }

    void SetPosition(const glm::vec2& position) { m_Transform.translation = position; }
    glm::vec2 GetPosition() const { return m_Transform.translation; }

private:
    App& m_App;
    bool m_HasKey;
    std::vector<std::shared_ptr<Util::Image>> m_HeroStandbyImages;
    std::vector<std::shared_ptr<Util::Image>> m_HeroMoveImages;
    std::vector<std::shared_ptr<Util::Image>> m_HeroKickImages;
};

#endif //HELLTAKER_HERO_HPP
