#include "App.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            ValidTask();
        }
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

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

    m_Root.Update();
}

bool App::CheckCollision(const glm::vec2 &newPosition) {
    // 角色的左上角與右下角座標
    glm::vec2 topLeft = newPosition - glm::vec2(50.0f, 50.0f);
    glm::vec2 bottomRight = newPosition + glm::vec2(50.0f, 50.0f);

    // 修正邊界 (左右修正以 100px 格子為基準)
    float leftBoundary = -800.0f;
    float rightBoundary = 800.0f;   // 修正，讓角色正好對齊 16 格
    float bottomBoundary = -450.0f;
    float topBoundary = 450.0f;    // 上下仍然沒問題

    // 檢查是否超出地圖邊界
    if (topLeft.x < leftBoundary || bottomRight.x > rightBoundary ||
        topLeft.y < bottomBoundary || bottomRight.y > topBoundary) {
        return true;  // 碰撞邊界
    }

    // 檢查地圖障礙物
    for (auto &row: m_grid) {
        for (auto &tile: row) {
            if (tile->isObstacle()) {
                glm::vec2 tilePos = tile->GetPosition();

                // 障礙物的邊界
                glm::vec2 tileTopLeft = tilePos - glm::vec2(50.0f, 50.0f);
                glm::vec2 tileBottomRight = tilePos + glm::vec2(50.0f, 50.0f);

                // 碰撞檢測（角色是否與障礙物重疊）
                if (topLeft.x < tileBottomRight.x && bottomRight.x > tileTopLeft.x &&
                    topLeft.y < tileBottomRight.y && bottomRight.y > tileTopLeft.y) {
                    return true;  // 碰撞到障礙物
                }
            }
        }
    }

    return false;  // 沒有碰撞
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
    glm::vec2 newPosition = m_Hero->GetPosition() + direction * 100.0f;

    std::shared_ptr<Box> box;
    if (IsBoxAtPosition(newPosition, box)) {
        glm::vec2 boxNewPosition = box->GetPosition() + direction * 100.0f;
        std::shared_ptr<Box> blockingBox;
        m_Hero->SetAnimation(m_HeroKickImages, true);
        if (IsWalkable(boxNewPosition) && !IsBoxAtPosition(boxNewPosition, blockingBox)) {
            // 可以推動箱子
            box->SetPosition(boxNewPosition);
            m_Hero->Move((int) direction.x, (int) direction.y, 16, 9);
            return;
        }
        // 如果不能推，角色也不能移動
    } else {
        m_Hero->SetAnimation(m_HeroMoveImages, true);
        if (IsWalkable(newPosition)) {
            m_Hero->Move((int) direction.x, (int) direction.y, 16, 9);
            return;
        }
    }
}