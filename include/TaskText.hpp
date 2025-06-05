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
    TaskText() : GameObject(std::make_unique<Util::Text>(HT_RESOURCE_DIR"/Font/Inkfree.ttf", 20,
                                                         "123",
                                                         Util::Color::FromName(Util::Colors::WHITE)), 100) {

    }

    void SetPosition(const glm::vec2& Position) {
        m_Transform.translation = Position;
    }

    void SetText(const std::string& text) {
        m_InputText = text;
        auto temp = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        if (temp) {
            temp->SetText(m_InputText);
        }
    }

    void NextPhase(const int phase) {
        std::string taskText = LoadTaskFromLine(HT_RESOURCE_DIR "/Map/StepOfMap.txt", phase);
        SetText(taskText);
    }

private:
    std::string LoadTaskFromLine(const std::string& filepath, int lineNumber) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            return "無法開啟任務檔案";
        }

        std::string line;
        int currentLine = 0;
        while (std::getline(file, line)) {
            if (currentLine == lineNumber) {
                return line;
            }
            ++currentLine;
        }

        return "任務資料不存在";
    }

    std::string m_InputText = "123";
};

#endif //TASKTEXT_HPP