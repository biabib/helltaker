#include "PhaseResourceManger.hpp"
#include "Util/Logger.hpp"

PhaseResourceManger::PhaseResourceManger() {
    m_TaskText = std::make_shared<TaskText>();
    m_TaskText2 = std::make_shared<TaskText>(); // ✅ 使用成員變數，不要重新宣告！

    m_TaskText->SetPosition({0.0f, -270.0f});
    m_TaskText2->SetPosition({0.0f, -330.0f});
}

void PhaseResourceManger::NextPhase() {
    if (static_cast<int>(m_Phase) >= 6) return;

    m_Phase = static_cast<Phase>(static_cast<int>(m_Phase) + 1);
    m_TaskText->NextPhase(static_cast<int>(m_Phase));
    m_TaskText2->SetText("Phase: " + std::to_string(static_cast<int>(m_Phase))); // ✅ 傳入 string
}