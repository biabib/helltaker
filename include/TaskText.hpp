#ifndef TASKTEXT_HPP
#define TASKTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"
#include "Util/Logger.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class TaskText : public Util::GameObject {
public:
    TaskText() : GameObject(std::make_unique<Util::Text>(HT_RESOURCE_DIR"/Font/CrimsonPro-Medium.ttf", 70,
                                                         "m_InputText",
                                                         Util::Color::FromName(Util::Colors::WHITE)), 100) {

    }

    void SetPosition(const glm::vec2& Position) {
        m_Transform.translation = Position;
    }

    void SetText(const std::string& text) {
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(text);
    }


private:
    std::string m_InputText;
};

#endif //TASKTEXT_HPP