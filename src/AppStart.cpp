#include <iostream>
#include <ostream>

#include "App.hpp"
#include <vector>
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_grid.clear();

    // 計算地圖偏移量以置中
    float offsetX = -(1600.0f / 2.0f)+50;
    float offsetY = (900.0f / 2.0f)-50;

    // 地圖設計（0 = 無地板, 1 = 有地板）
    std::vector<std::vector<int>> mapData = {
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}
    };

    // 初始化地圖網格
    for (int row = 0; row < mapData.size(); ++row) {
        std::vector<std::shared_ptr<Map>> tileRow;
        for (int col = 0; col < mapData[row].size(); ++col) {
            float worldX = offsetX + col * 100.0f;
            float worldY = offsetY - row * 100.0f;

            if (mapData[row][col] == 1) {
                auto floorGrid =  std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Floor/floor.png");
                tileRow.push_back(floorGrid);
                m_Root.AddChild(floorGrid);
            }
        }
        m_grid.push_back(tileRow);
    }

    auto box1 = std::make_shared<Box>(350, 300, HT_RESOURCE_DIR "/Image/Box/box.png");
    auto box2 = std::make_shared<Box>(550, 300, HT_RESOURCE_DIR "/Image/Box/box.png");
    m_boxes.push_back(box1);
    m_boxes.push_back(box2);

    // 加入場景
    for (auto& box : m_boxes) {
        LOG_DEBUG(box->GetPosition());
        box->SetZIndex(5);
        m_Root.AddChild(box);
    }
    LOG_DEBUG("fuck");
    // 初始化角色
    std::vector<std::string> HeroImages;
    HeroImages.reserve(12);
    for (int i = 1; i < 12; ++i) {
        HeroImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Standby/hero" + std::to_string(i) + ".png");
    }

    m_Hero = std::make_shared<AnimatedCharacter>(HeroImages);
    m_Hero->SetPosition({-750.0f, 0.0f}); // 初始位置
    m_Hero->SetZIndex(50);
    m_Hero->SetLooping(true);
    m_Root.AddChild(m_Hero);

    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;
}