#ifndef TASKTEXT_HPP
#define TASKTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

class TaskText : public Util::GameObject {
public:
    TaskText() : GameObject(std::make_unique<Util::Text>(HT_RESOURCE_DIR"/Font/Inkfree.ttf", 20,
                                         m_InputText,
                                         Util::Color::FromName(Util::Colors::WHITE)),100)
     {
//        m_Transform.translation = {0.0F, -270.F};
    }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
    void SetText(const std::string& text) {
        m_InputText = text;
        if (m_Text) {
            m_Text->SetText(m_InputText);
        }
    }
    void NextPhase(const int phase) {
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        temp->SetText(append_string_views(s_PhaseTasks[phase], s_Validation));
    }

private:
    inline static std::string append_string_views(std::string_view sv1, std::string_view sv2) {
        return std::string(sv1) + "\n" + std::string(sv2);
    }

    static constexpr std::string_view s_PhaseTasks[6] = {
            "30",
    };
    static constexpr std::string_view s_Validation = "Press Enter to validate";
    std::shared_ptr<Util::Text> m_Text;
    std::string m_InputText;

};


#endif //TASKTEXT_HPP
