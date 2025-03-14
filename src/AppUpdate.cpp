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
    double x = m_Hero->GetPosition().x;
    double y = m_Hero->GetPosition().y;
    if (Util::Input::IsKeyPressed(Util::Keycode::UP) || Util::Input::IsKeyPressed(Util::Keycode::W)) {
        m_Hero->SetPosition({x, y + 50});
        _sleep(10);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN) || Util::Input::IsKeyPressed(Util::Keycode::S)) {
        m_Hero->SetPosition({x, y - 50});
        _sleep(10);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT) || Util::Input::IsKeyPressed(Util::Keycode::D)) {
        m_Hero->SetPosition({x + 50, y});
        _sleep(10);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT) || Util::Input::IsKeyPressed(Util::Keycode::A)) {
        m_Hero->SetPosition({x - 50, y});
        _sleep(10);
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
