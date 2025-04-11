#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"
#include "Character.hpp"
#include "Map.hpp"
#include "Wall.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManger.hpp"
#include "AnimatedCharacter.hpp"
#include "Box.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    enum class Phase {
        CHANGE_CHARACTER_IMAGE,
        ABLE_TO_MOVE,
        COLLIDE_DETECTION,
        BEE_ANIMATION,
        OPEN_THE_DOORS,
        COUNTDOWN,
    };


    State m_CurrentState = State::START;
    Phase m_Phase = Phase::CHANGE_CHARACTER_IMAGE;

    Util::Renderer m_Root;

    std::shared_ptr<AnimatedCharacter> m_Hero;
    std::vector<std::string> m_HeroStandbyImages;
    std::vector<std::string> m_HeroMoveImages;
    std::vector<std::string> m_HeroKickImages;
    std::shared_ptr<PhaseResourceManger> m_PRM;
    std::vector<std::vector<int>> m_mapData;
    std::vector<std::vector<std::shared_ptr<Map>>> m_grid;
    std::vector<std::shared_ptr<Box>> m_boxes;
    bool m_EnterDown = false;
    bool CheckCollision(const glm::vec2& newPosition);
    void TryMoveHero(const glm::vec2& direction);
    bool IsWalkable(const glm::vec2& position);
    bool IsBoxAtPosition(const glm::vec2& position, std::shared_ptr<Box>& outBox);
};

#endif
