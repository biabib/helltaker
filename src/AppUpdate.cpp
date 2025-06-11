#include <filesystem>
#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::R) || m_Steps <= 0) {
        m_Root = Util::Renderer();  // 重建畫面根節點
        m_grid.clear();
        m_boxes.clear();
        m_enemies.clear();
        m_goals.clear();
        m_LockedBlocks.clear();
        m_HasKey = false;

        int currentPhase = m_PRM->GetCurrentPhase();
        std::string mapPath = HT_RESOURCE_DIR "/Maps/map" + std::to_string(static_cast<int>(currentPhase)) + ".txt";

        if (std::filesystem::exists(mapPath)) {
            m_mapData = MapStorage::LoadMap(mapPath);
            LoadMapFromData();  // 這裡會清空原本的 Root children
        }
        m_Root.AddChild(m_StepUI);
        m_Root.AddChild(m_LevelUI);
        m_Steps = m_StepRow[static_cast<int>(m_PRM->GetCurrentPhase())-1];
        m_StepText->SetText(std::to_string(m_Steps));
        m_Root.AddChild(m_StepText);
        m_Root.AddChild(m_PhaseText);
        m_Root.AddChild(m_Reload);  // 重新加入動畫物件
        m_Reload->SetCurrentFrame();
        m_Reload->SetLooping(false);
        m_Reload->SetVisible(true);
        m_Reload->Play();
        isReloading = true;
    }


    if(isReloading){
        if(m_Reload->IfAnimationEnds()) {
            m_Reload->SetVisible(false);
            isReloading = false;
            m_Root.RemoveChild(m_Reload);
        }
    }

    if (Util::Input::IsKeyDown(Util::Keycode::N)) {
        adjacent = true;
        TriggerLevelComplete();
    }

    if (Util::Input::IsKeyDown(Util::Keycode::UP) || Util::Input::IsKeyDown(Util::Keycode::W)) {
        TryMoveHero(glm::vec2(0, 1));
    }
    if (Util::Input::IsKeyDown(Util::Keycode::DOWN) || Util::Input::IsKeyDown(Util::Keycode::S)) {
        TryMoveHero(glm::vec2(0, -1));
    }
    if (Util::Input::IsKeyDown(Util::Keycode::LEFT) || Util::Input::IsKeyDown(Util::Keycode::A)) {
        TryMoveHero(glm::vec2(-1, 0));
    }
    if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) || Util::Input::IsKeyDown(Util::Keycode::D)) {
        TryMoveHero(glm::vec2(1, 0));
    }

    if (m_Hero->IfAnimationEnds()) {
        m_Hero->SetAnimation(m_HeroStandbyImages, true);
    }

    for (auto &enemy: m_enemies) {
        if (enemy->IfAnimationEnds()) {
            enemy->SetAnimation(m_EnemyStandbyImages, true);
        }
    }

    if (m_Key && m_Hero->GetPosition() == m_Key->GetPosition()) {
        m_HasKey = true;
        m_Key->SetVisible(false);
        LOG_DEBUG("Key obtained!");
    }

    if (!m_goals.empty()) {
        glm::vec2 goalPos = m_goals[0]->GetPosition();
        glm::vec2 heroPos = m_Hero->GetPosition();

        constexpr float tileSize = 100.0f;
        constexpr float epsilon = 1e-3f;

        float dx = std::abs(heroPos.x - goalPos.x);
        float dy = std::abs(heroPos.y - goalPos.y);

        adjacent =
                (std::abs(dx - tileSize) < epsilon && dy < epsilon) ||
                (std::abs(dy - tileSize) < epsilon && dx < epsilon);

        if (adjacent) {
            TriggerLevelComplete();
        }
    }
    for (auto it = m_enemies.begin(); it != m_enemies.end(); ) {
        const auto& enemy = *it;
        for (const auto& spike : m_Spikes) {
            if (spike->GetPosition() == enemy->GetPosition() && spike->IsActive()) {
                LOG_DEBUG("Enemy stepped on active spike!");
                m_Root.RemoveChild(enemy);
                it = m_enemies.erase(it);  // 移除敵人
                goto nextEnemy;  // 跳出內層迴圈
            }
        }
        ++it;
        nextEnemy:;
    }
    m_StepText->SetText(std::to_string(m_Steps));
    m_Root.Update();

}

bool App::IsBoxAtPosition(const glm::vec2 &position, std::shared_ptr<Box> &outBox) {
    for (auto &box: m_boxes) {
        if (box->GetPosition() == position) {
            outBox = box;
            return true;
        }
    }
    return false;
}

bool App::IsEnemyAtPosition(const glm::vec2 &position, std::shared_ptr<Enemy> &outEnemy) {
    for (auto &enemy: m_enemies) {
        if (enemy->GetPosition() == position) {
            outEnemy = enemy;
            return true;
        }
    }
    return false;
}

bool App::IsGoalAtPosition(const glm::vec2 &position) {
    for (const auto &goal: m_goals) {
        if (goal->GetPosition() == position) {
            return true;
        }
    }
    return false;
}

// 輔助函數：判斷某個位置是否可行走（沒有牆壁也沒有邊界）
bool App::IsWalkable(const glm::vec2 &position) {
    glm::vec2 topLeft = position - glm::vec2(50.0f, 50.0f);
    glm::vec2 bottomRight = position + glm::vec2(50.0f, 50.0f);

    float leftBoundary = -800.0f;
    float rightBoundary = 800.0f;
    float bottomBoundary = -450.0f;
    float topBoundary = 450.0f;


    // 邊界檢查
    if (topLeft.x < leftBoundary || bottomRight.x > rightBoundary ||
        topLeft.y < bottomBoundary || bottomRight.y > topBoundary) {
        return false;
    }

    // 障礙物檢查
    for (auto &row: m_grid) {
        for (auto &tile: row) {
            if (tile->isObstacle()) {
                if (std::find(m_LockedBlocks.begin(), m_LockedBlocks.end(), tile) != m_LockedBlocks.end()) {
                    continue;  // 跳過鎖的處理
                }
                glm::vec2 tilePos = tile->GetPosition();
                glm::vec2 tileTopLeft = tilePos - glm::vec2(50.0f, 50.0f);
                glm::vec2 tileBottomRight = tilePos + glm::vec2(50.0f, 50.0f);

                if (topLeft.x < tileBottomRight.x && bottomRight.x > tileTopLeft.x &&
                    topLeft.y < tileBottomRight.y && bottomRight.y > tileTopLeft.y) {
                    return false;
                }
            }
        }
    }

    return true;
}

// 移動角色，處理推箱子邏輯
void App::TryMoveHero(const glm::vec2 &direction) {
    glm::vec2 heroNewPos = m_Hero->GetPosition() + direction * 100.0f;

    std::shared_ptr<Box> box;
    std::shared_ptr<Enemy> enemy;

    if (direction.x < 0) m_Hero->m_Transform.scale.x = -1.0f;
    else if (direction.x > 0) m_Hero->m_Transform.scale.x = 1.0f;

    m_Steps-=1;
//    m_StepText->SetText(std::to_string(m_Steps));

//    for (const auto& spike : m_Spikes) {
//        if ((spike->GetPosition() == direction || spike->GetPosition() == m_Hero->GetPosition()) && spike->IsActive()) {
//            m_Steps--;  // 或觸發死亡、重置等處理
//
//            LOG_DEBUG("Hero stepped on active spike!");
//        }
//    }

    for (auto& spike : m_Spikes) {
        spike->OnStep(); // 切換狀態（如果是 Toggle）
    }

    // 嘗試推箱子
    if (IsBoxAtPosition(heroNewPos, box)) {
        glm::vec2 boxNewPos = box->GetPosition() + direction * 100.0f;

        std::shared_ptr<Box> blockingBox;
        std::shared_ptr<Enemy> blockingEnemy;

        bool canPush = TryUnlockLockedBlockAt(boxNewPos) &&
                       IsWalkable(boxNewPos) &&
                       !IsBoxAtPosition(boxNewPos, blockingBox) &&
                       !IsEnemyAtPosition(boxNewPos, blockingEnemy) &&
                       !IsGoalAtPosition(boxNewPos);

        m_Hero->SetAnimation(m_HeroKickImages, true);

        if (canPush) {
            box->SetPosition(boxNewPos);
        }

        return;
    }

    // 嘗試推敵人
    if (IsEnemyAtPosition(heroNewPos, enemy)) {
        glm::vec2 enemyNewPos = enemy->GetPosition() + direction * 100.0f;

        bool pushToGoal = IsGoalAtPosition(enemyNewPos);
        bool blockedByWallOrLock = !TryUnlockLockedBlockAt(enemyNewPos) || !IsWalkable(enemyNewPos);

        std::shared_ptr<Box> blockingBox;
        std::shared_ptr<Enemy> blockingEnemy;
        bool blockedByBox = IsBoxAtPosition(enemyNewPos, blockingBox);
        bool blockedByEnemy = IsEnemyAtPosition(enemyNewPos, blockingEnemy);

        m_Hero->SetAnimation(m_HeroKickImages, true);
        enemy->SetAnimation(m_EnemyPushedImages, true);

        if (!blockedByWallOrLock && !blockedByBox && !blockedByEnemy && !pushToGoal) {
            enemy->SetPosition(enemyNewPos);
            if (direction.x > 0) enemy->m_Transform.scale.x = -1.0f;
            else if (direction.x < 0) enemy->m_Transform.scale.x = 1.0f;
        } else {
            m_Root.RemoveChild(enemy);
            m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), enemy), m_enemies.end());
        }

        return;
    }



    // 一般移動
    if (IsWalkable(heroNewPos) && !IsGoalAtPosition(heroNewPos)) {
        if (!TryUnlockLockedBlockAt(heroNewPos)) {
            m_Steps++;
//            m_StepText->SetText(std::to_string(m_Steps));
            return; // 有鎖但沒鑰匙，不能走
        }

        m_Hero->SetAnimation(m_HeroMoveImages, true);
        bool isPushingBox = false;
        bool isPushingEnemy = false;
        bool canPush = true;
        m_Hero->Move((int) direction.x, (int) direction.y, 16, 9);
        for (const auto& spike : m_Spikes) {
            if (spike->GetPosition() == m_Hero->GetPosition() && spike->IsActive()) {
//                m_Steps--;
                beMinus = 2;
                LOG_DEBUG("Hero stepped on active spike!");
            }
        }
        if(beMinus>0){
            m_Steps--;
            beMinus--;
        }
        return;

    }




}
bool App::TryUnlockLockedBlockAt(const glm::vec2& position) {
    for (auto it = m_LockedBlocks.begin(); it != m_LockedBlocks.end(); ++it) {
        if ((*it)->GetPosition() == position) {
            if (m_HasKey) {
                m_Root.RemoveChild(*it);
                m_LockedBlocks.erase(it);
                m_HasKey = false; //  鑰匙為一次性
                LOG_DEBUG("Unlocked LockedBlock at ({}, {})", position.x, position.y);
                return true;
            } else {
                return false;
            }
        }
    }
    return true; // 沒鎖，可以通過
}

void App::TriggerLevelComplete() {
    ValidTask();
    m_Root.AddChild(m_StepUI);
    m_Root.AddChild(m_LevelUI);
    m_Steps = m_StepRow[static_cast<int>(m_PRM->GetCurrentPhase())-1];
    m_StepText->SetText(std::to_string(m_Steps));
    m_Root.AddChild(m_StepText);
    m_PhaseText->SetText(std::to_string(m_PRM->GetCurrentPhase()));
    m_Root.AddChild(m_PhaseText);
    m_Root.AddChild(m_Reload);
    m_Reload->SetCurrentFrame();
    m_Reload->SetLooping(false);
    m_Reload->SetVisible(true);
    m_Reload->Play();
    isReloading = true;
}
