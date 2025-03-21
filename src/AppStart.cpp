#include "App.hpp"
#include <vector>
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_grid.clear();

    // 計算地圖偏移量以置中
    float offsetX = (1600.0f - (16 * 100.0f)) / 2.0f;
    float offsetY = (900.0f - (9 * 100.0f)) / 2.0f;

    // 初始化地圖網格，並確保地圖置中
    for (int row = 0; row < 9; ++row) {
        std::vector<Map> tileRow;
        for (int col = 0; col < 16; ++col) {
            float worldX = offsetX + col * 100.0f;  // 計算位置，使地圖置中
            float worldY = offsetY + row * 100.0f;  // 計算位置，使地圖置中
            tileRow.emplace_back(worldX, worldY, HT_RESOURCE_DIR "/Image/Background/labFloor0002.png");
        }
        m_grid.push_back(tileRow);
    }

    // 初始化角色
    std::vector<std::string> HeroImages;
    HeroImages.reserve(12);
    for (int i = 1; i < 12; ++i) {
        HeroImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Standby/hero" + std::to_string(i) + ".png");
    }

    m_Hero = std::make_shared<AnimatedCharacter>(HeroImages);
    m_Hero->SetPosition({-700.0f, -450.0f}); // 初始位置
    m_Hero->SetZIndex(50);
    m_Hero->SetLooping(true);
    m_Root.AddChild(m_Hero);

    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;
}