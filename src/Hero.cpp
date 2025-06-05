//
// Created by USER on 2025/5/4.
//
#include "Hero.hpp"
#include "Box.hpp"
#include "Enemy.hpp"

Hero::Hero(App& app, const std::vector<std::string>& AnimationPaths)
        : m_App(app), m_HasKey(false) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, true, 60, true, 0);
}

void Hero::Move(const glm::vec2& direction, bool& isPushingBox, bool& isPushingEnemy, bool& canPush) {
    glm::vec2 newPosition = m_Transform.translation + direction * 100.0f;

    std::shared_ptr<Box> box;
    std::shared_ptr<Enemy> enemy;

    if (IsAtPosition(newPosition)) {
        // 嘗試推箱子
        if (IsBoxAtPosition(newPosition, box)) {
            // 推箱子的邏輯
            glm::vec2 boxNewPos = box->GetPosition() + direction * 100.0f;
            if (canPush) {
                box->SetPosition(boxNewPos);
                isPushingBox = true;
            }
        }

        // 嘗試推敵人
        if (IsEnemyAtPosition(newPosition, enemy)) {
            glm::vec2 enemyNewPos = enemy->GetPosition() + direction * 100.0f;
            if (!IsBoxAtPosition(enemyNewPos, box) && !IsEnemyAtPosition(enemyNewPos, enemy)) {
                enemy->SetPosition(enemyNewPos);
                isPushingEnemy = true;
            }
        }

        // 一般移動
        if (IsWalkable(newPosition)) {
            SetPosition(newPosition);
        }
    }
}

bool Hero::IsAtPosition(const glm::vec2& position) {
    return m_Transform.translation == position;
}



bool Hero::IfAnimationEnds() const {
    // 判斷動畫是否結束
    return false;
}
// 检查位置是否有箱子
bool Hero::IsBoxAtPosition(const glm::vec2& position, std::shared_ptr<Box>& outBox) {
    for (auto &box : m_App.GetBoxes()) {
        if (box->GetPosition() == position) {
            outBox = box;
            return true;
        }
    }
    return false;
}

// 检查位置是否有敌人
bool Hero::IsEnemyAtPosition(const glm::vec2& position, std::shared_ptr<Enemy>& outEnemy) {
    for (auto &enemy : m_App.GetEnemies()) {
        if (enemy->GetPosition() == position) {
            outEnemy = enemy;
            return true;
        }
    }
    return false;
}

// 检查位置是否有目标
bool Hero::IsGoalAtPosition(const glm::vec2& position) {
    for (const auto &goal : m_App.GetGoals()) {
        if (goal->GetPosition() == position) {
            return true;
        }
    }
    return false;
}

bool Hero::IsWalkable(const glm::vec2 &position) {
    glm::vec2 topLeft = position - glm::vec2(50.0f, 50.0f);
    glm::vec2 bottomRight = position + glm::vec2(50.0f, 50.0f);

    float leftBoundary = -800.0f;
    float rightBoundary = 800.0f;
    float bottomBoundary = -450.0f;
    float topBoundary = 450.0f;

    // 边界检查
    if (topLeft.x < leftBoundary || bottomRight.x > rightBoundary ||
        topLeft.y < bottomBoundary || bottomRight.y > topBoundary) {
        return false;
    }

    // 障碍物检查
    for (auto &row: m_App.GetGrid()) {
        for (auto &tile: row) {
            if (tile->isObstacle()) {
                if (std::find(m_App.GetLockedBlocks().begin(), m_App.GetLockedBlocks().end(), tile) != m_App.GetLockedBlocks().end()) {
                    continue;  // 跳过锁住的格子
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