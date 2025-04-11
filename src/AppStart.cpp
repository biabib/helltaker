#include <iostream>
#include <ostream>

#include "App.hpp"
#include <vector>
#include "Util/Logger.hpp"
#include "MapStorage.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_grid.clear();

    // Standby
    for (int i = 1; i < 12; ++i) {
        m_HeroStandbyImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Standby/hero" + std::to_string(i) + ".png");
    }
    // Move
    for (int i = 1; i < 6; ++i) {
        m_HeroMoveImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Move/move" + std::to_string(i) + ".png");
    }

    // Kick
    for (int i = 1; i < 7; ++i) {
        m_HeroKickImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Kick/kick" + std::to_string(i) + ".png");
    }


    for (int i = 1; i < 12; ++i) {
        m_EnemyStandbyImages.emplace_back(HT_RESOURCE_DIR "/Image/Enemy/Standby/enemy" + std::to_string(i) + ".png");
    }

    for (int i = 1; i < 6; ++i) {
        m_EnemyPushedImages.emplace_back(HT_RESOURCE_DIR "/Image/Enemy/Pushed/beKicked" + std::to_string(i) + ".png");
    }

    for (int i = 1; i < 12; ++i) {
        m_GoalImages.emplace_back(HT_RESOURCE_DIR "/Image/Goal/Goal-1_" + std::to_string(i) + ".png");
    }

    // 計算地圖偏移量以置中
    float offsetX = -(1600.0f / 2.0f)+50;
    float offsetY = (900.0f / 2.0f)-50;

    // 地圖設計（0 = 無地板, 1 = 有地板,2 = 箱子, 3 = 牆壁, 4 = 敵人）
    m_mapData = MapStorage::LoadMap(HT_RESOURCE_DIR "/Maps/map1.txt");


    // 初始化地圖網格
    for (int row = 0; row < m_mapData.size(); ++row) {
        std::vector<std::shared_ptr<Map>> tileRow;
        for (int col = 0; col < m_mapData[row].size(); ++col) {
            float worldX = offsetX + col * 100.0f;
            float worldY = offsetY - row * 100.0f;

            if (m_mapData[row][col] == 1) {
                auto floorGrid = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Floor/floor.png");
                tileRow.push_back(floorGrid);
                m_Root.AddChild(floorGrid);
            } else if (m_mapData[row][col] == 2) {
                auto floorGrid = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Floor/floor.png");
                tileRow.push_back(floorGrid);
                m_Root.AddChild(floorGrid);
                auto box = std::make_shared<Box>(worldX, worldY, HT_RESOURCE_DIR "/Image/Box/box.png");
                m_boxes.push_back(box);
                m_Root.AddChild(box);
                box->SetZIndex(5);
            } else if (m_mapData[row][col] == 3) {
                auto floorGrid = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Floor/floor.png");
                tileRow.push_back(floorGrid);
                m_Root.AddChild(floorGrid);
                auto wallGrid = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Wall/wall2.png", true);
                tileRow.push_back(wallGrid);
                m_Root.AddChild(wallGrid);
                wallGrid->SetZIndex(3);
            }else if(m_mapData[row][col] == 4) {
                auto floorGrid = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Floor/floor.png");
                tileRow.push_back(floorGrid);
                m_Root.AddChild(floorGrid);
                auto enemy = std::make_shared<Enemy>(m_EnemyStandbyImages);
                enemy->SetPosition({worldX, worldY});
                enemy->SetZIndex(5);
                enemy->SetLooping(true);
                m_enemies.push_back(enemy);
                m_Root.AddChild(enemy);
            }else if (m_mapData[row][col] == 5) {
                auto floorGrid = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Floor/floor.png");
                tileRow.push_back(floorGrid);
                m_Root.AddChild(floorGrid);
                auto goal = std::make_shared<Goal>(m_GoalImages);
                goal->SetPosition({worldX, worldY});
                goal->SetZIndex(5);
                goal->SetLooping(true);
                m_goals.push_back(goal);
                m_Root.AddChild(goal);
            }
        }
        m_grid.push_back(tileRow);
    }

    LOG_DEBUG("fuck");
    // 初始化角色

    m_Hero = std::make_shared<AnimatedCharacter>(m_HeroStandbyImages);
    m_Hero->SetPosition({-750.0f, 0.0f}); // 初始位置
    m_Hero->SetZIndex(5);
    m_Hero->SetLooping(true);
    m_Root.AddChild(m_Hero);


    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;
}