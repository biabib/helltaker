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
    Core::Matrices data;

    // 繪製地圖格子
    for (auto& row : m_grid) {
        for (auto& tile : row) {
            tile.draw(data);
        }
    }

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

// 碰撞檢查函數
bool App::CheckCollision(const glm::vec2& newPosition) {
    // 檢查是否超出邊界
    if (newPosition.x < -800 || newPosition.x > 800 || newPosition.y < -450 || newPosition.y > 450) {
        return true;
    }

    // 檢查地圖格子是否為障礙物
    for (auto& row : m_grid) {
        for (auto& tile : row) {
            if (tile.isObstacle() && glm::abs(newPosition.x - tile.getPosition().x) < 50.0f &&
                glm::abs(newPosition.y - tile.getPosition().y) < 50.0f) {
                return true;
            }
        }
    }

    return false;
}
