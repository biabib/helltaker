#include "PhaseResourceManger.hpp"

#include "Util/Logger.hpp"

PhaseResourceManger::PhaseResourceManger() {
    m_TaskText = std::make_shared<TaskText>();
    m_Background = std::make_shared<BackgroundImage>();
}

void PhaseResourceManger::NextPhase() {
    if (static_cast<int>(m_Phase) >= 16) return;

    m_Phase = static_cast<Phase>(static_cast<int>(m_Phase) + 1);

    m_Background->NextPhase(static_cast<int>(m_Phase));
    m_TaskText->NextPhase(static_cast<int>(m_Phase));
}