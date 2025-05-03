////
//// Created by USER on 2025/5/4.
////
//#include "MapLoader.hpp"
//#include <filesystem>
//#include "MapStorage.hpp"
//#include "Util/Renderer.hpp"
//
//
//
//void MapLoader::ReloadMap(App& app) {
//    // 重新建立畫面根節點
//    app.m_Root = Util::Renderer();
//
//    // 清空所有遊戲物件與狀態
//    app.m_grid.clear();
//    app.m_boxes.clear();
//    app.m_enemies.clear();
//    app.m_goals.clear();
//    app.m_LockedBlocks.clear();
//    app.m_HasKey = false;
//
//    // 讀取地圖
//    Phase currentPhase = app.m_PRM->GetCurrentPhase();
//    std::string mapPath = HT_RESOURCE_DIR "/Maps/map" + std::to_string(static_cast<int>(currentPhase)) + ".txt";
//
//    if (std::filesystem::exists(mapPath)) {
//        app.m_mapData = MapStorage::LoadMap(mapPath);
//        LoadMapFromData(app); // 根據 mapData 載入物件
//    }
//
//    // 重新加入 UI 與動畫物件
//    app.m_Root.AddChild(app.m_StepUI);
//    app.m_Root.AddChild(app.m_LevelUI);
//    app.m_Root.AddChild(app.m_Reload);
//
//    app.m_Reload->SetCurrentFrame();
//    app.m_Reload->SetLooping(false);
//    app.m_Reload->SetVisible(true);
//    app.m_Reload->Play();
//
//    app.isReloading = true;
//}
//
//void MapLoader::LoadMapFromData(App& app) {
//    const auto& data = app.m_mapData;
//    const float tileSize = 100.0f;
//    const glm::vec2 offset = glm::vec2(-800.0f, 450.0f); // 左上角為(0,0)
//
//    int rows = static_cast<int>(data.size());
//    int cols = rows > 0 ? static_cast<int>(data[0].size()) : 0;
//
//    app.m_grid.resize(rows);
//
//    for (int i = 0; i < rows; ++i) {
//        app.m_grid[i].resize(cols);
//
//        for (int j = 0; j < cols; ++j) {
//            glm::vec2 pos = offset + glm::vec2(j * tileSize, -i * tileSize);  // 向右x+，向下y-
//
//            char ch = data[i][j];
//
//            auto tile = std::make_shared<Tile>();
//            tile->SetPosition(pos);
//            tile->SetType(Tile::Type::FLOOR);
//
//            switch (ch) {
//                case '#': // 牆
//                    tile->SetType(Tile::Type::WALL);
//                    break;
//                case 'B': { // 箱子
//                    auto box = std::make_shared<Box>();
//                    box->SetPosition(pos);
//                    app.m_boxes.push_back(box);
//                    app.m_Root.AddChild(box);
//                    break;
//                }
//                case 'E': { // 敵人
//                    auto enemy = std::make_shared<Enemy>();
//                    enemy->SetPosition(pos);
//                    enemy->SetAnimation(app.m_EnemyStandbyImages, true);
//                    app.m_enemies.push_back(enemy);
//                    app.m_Root.AddChild(enemy);
//                    break;
//                }
//                case 'G': { // 目標
//                    auto goal = std::make_shared<Goal>();
//                    goal->SetPosition(pos);
//                    app.m_goals.push_back(goal);
//                    app.m_Root.AddChild(goal);
//                    break;
//                }
//                case 'K': { // 鑰匙
//                    app.m_Key = std::make_shared<Key>();
//                    app.m_Key->SetPosition(pos);
//                    app.m_Root.AddChild(app.m_Key);
//                    break;
//                }
//                case 'L': { // 鎖定區塊
//                    auto locked = std::make_shared<Tile>();
//                    locked->SetType(Tile::Type::WALL);
//                    locked->SetPosition(pos);
//                    app.m_LockedBlocks.push_back(locked);
//                    app.m_Root.AddChild(locked);
//                    break;
//                }
//                case 'P': { // 玩家
//                    app.m_Hero = std::make_shared<AnimatedCharacter>();
//                    app.m_Hero->SetPosition(pos);
//                    app.m_Hero->SetAnimation(app.m_HeroStandbyImages, true);
//                    app.m_Root.AddChild(app.m_Hero);
//                    break;
//                }
//                default:
//                    break;
//            }
//
//            app.m_grid[i][j] = tile;
//            app.m_Root.AddChild(tile);
//        }
//    }
//}