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

    // 繪製地圖格子


    // 角色移動控制（加入碰撞檢查）
    if (Util::Input::IsKeyDown(Util::Keycode::UP) || Util::Input::IsKeyDown(Util::Keycode::W)) {
        if (!CheckCollision(m_Hero->GetPosition() + glm::vec2(0, 100.0f))) {  // 向上移動後的檢查
            m_Hero->Move(0, 1, 16, 9);
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::DOWN) || Util::Input::IsKeyDown(Util::Keycode::S)) {
        if (!CheckCollision(m_Hero->GetPosition() + glm::vec2(0, -100.0f))) {  // 向下移動後的檢查
            m_Hero->Move(0, -1, 16, 9);
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::LEFT) || Util::Input::IsKeyDown(Util::Keycode::A))  {
        if (!CheckCollision(m_Hero->GetPosition() + glm::vec2(-100.0f, 0))) {  // 向左移動後的檢查
            m_Hero->Move(-1, 0, 16, 9);
        }
    }
    if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) || Util::Input::IsKeyDown(Util::Keycode::D)) {
        if (!CheckCollision(m_Hero->GetPosition() + glm::vec2(100.0f, 0))) {  // 向右移動後的檢查
            m_Hero->Move(1, 0, 16, 9);
        }
    }

    m_Root.Update();
}

bool App::CheckCollision(const glm::vec2& newPosition) {
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
    for (auto& row : m_grid) {
        for (auto& tile : row) {
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
