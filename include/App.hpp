#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export


#include "Util/Renderer.hpp"
#include "Util/SFX.hpp"
#include "Character.hpp"
#include "Map.hpp"
#include "Enemy.hpp"
#include "Goal.hpp"
#include "Hero.hpp"
#include "Util/Text.hpp"
#include "PhaseResourceManger.hpp"
#include "AnimatedCharacter.hpp"
#include "Box.hpp"
#include "MapStorage.hpp"
#include "Key.hpp"
#include "Reload.hpp"
#include "LockedBlock.hpp"
#include "Spike.hpp"
#include "Util/Logger.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    const char* tranfer(Phase p) {
        switch (p) {
            case Phase::None: return "0";
            case Phase::Quest1: return "1";
            case Phase::Quest2: return "2";
            case Phase::Quest3: return "3";
            case Phase::Quest4: return "4";
            case Phase::Quest5: return "5";
            case Phase::Quest6: return "6";
            default: return "null";
        }
    }

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

    std::vector<std::shared_ptr<Box>>& GetBoxes() { return m_boxes; }
    std::vector<std::shared_ptr<Enemy>>& GetEnemies() { return m_enemies; }
    std::vector<std::shared_ptr<Goal>>& GetGoals() { return m_goals; }
    std::vector<std::vector<std::shared_ptr<Map>>>& GetGrid() { return m_grid; }
    std::vector<std::shared_ptr<LockedBlock>>& GetLockedBlocks() { return m_LockedBlocks; }



private:



    State m_CurrentState = State::START;
    int m_Phase = 1;

    Util::Renderer m_Root;

    std::shared_ptr<AnimatedCharacter> m_Hero;
    std::vector<std::string> m_HeroStandbyImages;
    std::vector<std::string> m_HeroMoveImages;
    std::vector<std::string> m_HeroKickImages;
    std::shared_ptr<PhaseResourceManger> m_PRM;
    std::vector<std::vector<int>> m_mapData;
    std::vector<std::vector<std::shared_ptr<Map>>> m_grid;
    std::vector<std::shared_ptr<Box>> m_boxes;
    std::vector<std::shared_ptr<Enemy>> m_enemies;
    std::vector<std::string> m_EnemyStandbyImages;
    std::vector<std::string> m_EnemyPushedImages;
    std::vector<std::shared_ptr<Goal>> m_goals;
    std::vector<std::string> m_GoalImages;
    std::shared_ptr<AnimatedCharacter> m_Reload;
    std::vector<std::string> m_ReloadImages;
    std::shared_ptr<Key> m_Key;
    std::vector<std::string> m_KeyImages;
    std::vector<std::shared_ptr<LockedBlock>> m_LockedBlocks;
    std::shared_ptr<Character> m_StepUI;
    std::shared_ptr<Character> m_LevelUI;

    std::vector<std::shared_ptr<Spike>> m_Spikes;
    std::vector<std::string> m_SpikeUpImages;
    std::vector<std::string> m_SpikeDownImages;


    std::vector<int> m_StepRow;
    std::shared_ptr<TaskText> m_StepText;
    std::shared_ptr<TaskText> m_PhaseText;

    std::shared_ptr<Util::SFX> m_SFX;

    int m_Steps = 0;

    int beMinus = 0;

    bool m_EnterDown = false;
    bool isReloading = false;
    bool m_HasKey = false;
    bool adjacent = false;
    void ValidTask();
    void LoadMapFromData();
    void TryMoveHero(const glm::vec2& direction);
    void TriggerLevelComplete();
    bool TryUnlockLockedBlockAt(const glm::vec2& position);
    bool IsWalkable(const glm::vec2& position);
    bool IsBoxAtPosition(const glm::vec2& position, std::shared_ptr<Box>& outBox);
    bool IsEnemyAtPosition(const glm::vec2& position, std::shared_ptr<Enemy>& outEnemy);
    bool IsGoalAtPosition(const glm::vec2 &position);
};

#endif
