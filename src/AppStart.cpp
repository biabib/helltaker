#include "App.hpp"
#include <vector>
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_grid.clear();

    // 初始化地圖網格
    for (int row = 0; row < 9; ++row) {
        std::vector<Map> tileRow;
        for (int col = 0; col < 16; ++col) {
            float worldX = (col - 8) * 100.0f;  // 向左偏移 8 格
            float worldY = (4 - row) * 100.0f;  // 讓 row=0 在最上方，row=8 在最下方
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