#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {

    // TODO: Add your own logics to finish the tasks in README.md

    /*
     *  Do not touch the code below as they serve the purpose for validating the tasks,
     *  rendering the frame, and exiting the game.
    */

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
    // 角色移動控制
    if (Util::Input::IsKeyDown(Util::Keycode::UP) || Util::Input::IsKeyDown(Util::Keycode::W)) {
        m_Hero->Move(0, 1, 16, 9);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::DOWN) || Util::Input::IsKeyDown(Util::Keycode::S)) {
        m_Hero->Move(0, -1, 16, 9);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::LEFT) || Util::Input::IsKeyDown(Util::Keycode::A))  {
        m_Hero->Move(-1, 0, 16, 9);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::RIGHT) || Util::Input::IsKeyDown(Util::Keycode::D)) {
        m_Hero->Move(1, 0, 16, 9);
    }

//    if (m_Giraffe->IfCollides(m_Chest)) {
//        m_Chest->SetVisible(false);
//    }
//
//    if (m_Phase == Phase::OPEN_THE_DOORS) {
//        for(int i =0;  i<3;i++) {
//            if (m_Giraffe->IfCollides(m_Doors[i])) {
//                if (m_Doors[i]->GetImagePath() != "/Image/Character/door_open.png")
//                    m_Doors[i]->SetImage(GA_RESOURCE_DIR"/Image/Character/door_open.png");
//            }
//        }
//    }

    m_Root.Update();
}
