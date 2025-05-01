#include "App.hpp"
#include "Util/Logger.hpp"
#include "MapStorage.hpp"
#include <cmath>
#include <filesystem>

/**
 * @brief The function to validate the tasks.
 * @warning Do not modify this function.
 * @note See README.md for the task details.
 */


void App::ValidTask() {
    LOG_DEBUG("Validating the task {}", static_cast<int>(m_PRM->GetCurrentPhase()));

    if (m_goals.empty()) return;

    const auto goalPos = m_goals[0]->GetPosition();
    const auto heroPos = m_Hero->GetPosition();

    constexpr float tileSize = 100.0f;
    float dx = std::abs(heroPos.x - goalPos.x);
    float dy = std::abs(heroPos.y - goalPos.y);

    bool adjacent =
            (dx == tileSize && dy == 0.0f) ||
            (dy == tileSize && dx == 0.0f);

    if (!adjacent) return;

    // 清除現有物件與狀態
    m_Root = Util::Renderer();  // 清空畫面
    m_grid.clear();
    m_boxes.clear();
    m_enemies.clear();
    m_goals.clear();
    m_HasKey = false;

    // 換階段
    m_PRM->NextPhase();
    Phase newPhase = m_PRM->GetCurrentPhase();

    // 判斷新地圖檔案是否存在
    std::string mapPath = HT_RESOURCE_DIR "/Maps/map" + std::to_string(static_cast<int>(newPhase)) + ".txt";
    if (!std::filesystem::exists(mapPath)) {
        LOG_DEBUG("No more maps. Game complete.");
        return;
    }

    m_mapData = MapStorage::LoadMap(mapPath);

    // 只載入新的地圖與角色，不重新載入資源
    LoadMapFromData();
}

