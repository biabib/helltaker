#include <iostream>
#include <ostream>

#include "App.hpp"
#include <vector>



void App::Start() {
    LOG_TRACE("Start");

    m_grid.clear();
    m_HeroStandbyImages.clear();
    m_HeroMoveImages.clear();
    m_HeroKickImages.clear();
    m_EnemyStandbyImages.clear();
    m_EnemyPushedImages.clear();
    m_GoalImages.clear();
    m_KeyImages.clear();
    m_ReloadImages.clear();

    for (int i = 1; i < 12; ++i)
        m_HeroStandbyImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Standby/hero" + std::to_string(i) + ".png");

    for (int i = 1; i < 6; ++i)
        m_HeroMoveImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Move/move" + std::to_string(i) + ".png");

    for (int i = 1; i < 7; ++i)
        m_HeroKickImages.emplace_back(HT_RESOURCE_DIR "/Image/Hero/Kick/kick" + std::to_string(i) + ".png");

    for (int i = 1; i < 12; ++i)
        m_EnemyStandbyImages.emplace_back(HT_RESOURCE_DIR "/Image/Enemy/Standby/enemy" + std::to_string(i) + ".png");

    for (int i = 1; i < 6; ++i)
        m_EnemyPushedImages.emplace_back(HT_RESOURCE_DIR "/Image/Enemy/Pushed/beKicked" + std::to_string(i) + ".png");

    for (int i = 1; i < 12; ++i)
        m_GoalImages.emplace_back(HT_RESOURCE_DIR "/Image/Goal/Goal-1_" + std::to_string(i) + ".png");

    for (int i = 1; i < 12; ++i)
        m_KeyImages.emplace_back(HT_RESOURCE_DIR "/Image/Key/key" + std::to_string(i) + ".png");

    for (int i = 1; i < 29; ++i)
        m_ReloadImages.emplace_back(HT_RESOURCE_DIR "/Image/Reload/transition_" + std::to_string(i+1) + ".png");

    for (int i = 1; i <= 4; ++i) {
        m_SpikeUpImages.emplace_back(HT_RESOURCE_DIR "/Image/Spike/spike" + std::to_string(i+4) + ".png");
        m_SpikeDownImages.emplace_back(HT_RESOURCE_DIR "/Image/Spike/spike" + std::to_string(i) + ".png");
    }


    if (m_Phase == Phase::Quest1)
        m_mapData = MapStorage::LoadMap(HT_RESOURCE_DIR "/Maps/map1.txt");

    m_Hero = std::make_shared<AnimatedCharacter>(m_HeroStandbyImages);

    LoadMapFromData();

    m_StepUI = std::make_shared<Character>(HT_RESOURCE_DIR "/Image/UI/UI.png");
    m_LevelUI = std::make_shared<Character>(HT_RESOURCE_DIR "/Image/UI/UI.png");
    m_StepUI->SetPosition({-650,-200});
    m_StepUI->SetZIndex(10);
    m_StepUI->m_Transform.scale.x = 0.8f;
    m_StepUI->m_Transform.scale.y = 0.8f;
    m_LevelUI->SetPosition({650,-200});
    m_LevelUI->SetZIndex(10);
    m_LevelUI->m_Transform.scale.x = -0.8f;
    m_LevelUI->m_Transform.scale.y = 0.8f;
    m_Root.AddChild(m_StepUI);
    m_Root.AddChild(m_LevelUI);

    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());

    m_CurrentState = State::UPDATE;

    m_Reload = std::make_shared<AnimatedCharacter>(m_ReloadImages);
    m_Reload->SetPosition({0.0f , 0.0f});
    m_Reload->SetZIndex(50);
    m_Reload->SetLooping(false);
    m_Reload->SetVisible(false);  // 不顯示
    m_Reload->Pause();            // 停止播放
    m_Root.AddChild(m_Reload);
    isReloading = false;          // 不進入播放流程
}

void App::LoadMapFromData() {
    float offsetX = -(1600.0f / 2.0f) + 50;
    float offsetY = (900.0f / 2.0f) - 50;


    for (int row = 0; row < m_mapData.size(); ++row) {
        std::vector<std::shared_ptr<Map>> tileRow;
        for (int col = 0; col < m_mapData[row].size(); ++col) {
            float worldX = offsetX + col * 100.0f;
            float worldY = offsetY - row * 100.0f;

            auto tile = m_mapData[row][col];

            auto floorGrid = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Floor/floor.png");
            if (tile != 0) {
                tileRow.push_back(floorGrid);
                m_Root.AddChild(floorGrid);
            }

            switch (tile) {
                case 2: {
                    auto box = std::make_shared<Box>(worldX, worldY, HT_RESOURCE_DIR "/Image/Box/box.png");
                    m_boxes.push_back(box);
                    box->SetZIndex(5);
                    m_Root.AddChild(box);
                    break;
                }
                case 3: {
                    auto wall = std::make_shared<Map>(worldX, worldY, HT_RESOURCE_DIR "/Image/Wall/wall2.png", true);
                    wall->SetZIndex(3);
                    tileRow.push_back(wall);
                    m_Root.AddChild(wall);
                    break;
                }
                case 4: {
                    auto enemy = std::make_shared<Enemy>(m_EnemyStandbyImages);
                    enemy->SetPosition({worldX, worldY});
                    enemy->SetZIndex(5);
                    enemy->SetLooping(true);
                    m_enemies.push_back(enemy);
                    m_Root.AddChild(enemy);
                    break;
                }
                case 5: {
                    auto goal = std::make_shared<Goal>(m_GoalImages);
                    goal->SetPosition({worldX, worldY});
                    goal->SetZIndex(5);
                    goal->SetLooping(true);
                    m_goals.push_back(goal);
                    m_Root.AddChild(goal);
                    break;
                }
                case 6: {
                    m_Hero->SetPosition({worldX, worldY});
                    m_Hero->SetZIndex(5);
                    m_Root.AddChild(m_Hero);
                    break;
                }
                case 7: {
                    m_Key = std::make_shared<Key>(m_KeyImages);
                    m_Key->SetPosition({worldX, worldY});
                    m_Key->SetZIndex(3);
                    m_Root.AddChild(m_Key);
                    break;
                }
                case 8: {
                    auto locked = std::make_shared<LockedBlock>(worldX, worldY, HT_RESOURCE_DIR "/Image/Wall/LockedBlock.png");
                    locked->SetZIndex(3);
                    tileRow.push_back(locked);
                    m_LockedBlocks.push_back(locked);
                    m_Root.AddChild(locked);
                    break;
                }
                case 9: {
                    auto spike = std::make_shared<Spike>(
                            m_SpikeUpImages,
                            m_SpikeDownImages,
                            SpikeType::Toggle,
                            1  // 每 2 步切換一次狀態
                    );
                    spike->SetPosition({worldX, worldY});
                    spike->SetZIndex(4);
                    spike->SetLooping(false);
                    m_Spikes.push_back(spike);
                    m_Root.AddChild(spike);
                    break;
                }
                case 10: { // 代表 Static Spike（始終為上升）
                    auto spike = std::make_shared<Spike>(
                            m_SpikeUpImages,
                            m_SpikeDownImages,
                            SpikeType::Static
                    );
                    spike->SetPosition({worldX, worldY});
                    spike->SetZIndex(4);
                    spike->SetLooping(false);
                    m_Spikes.push_back(spike);
                    m_Root.AddChild(spike);
                    break;
                }
                default:
                    break;
            }
        }


        m_grid.push_back(tileRow);
    }
}