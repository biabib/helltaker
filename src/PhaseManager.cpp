#include "PhaseResourceManger.hpp"
#include "Util/Logger.hpp"

PhaseResourceManger::PhaseResourceManger() {
}

void PhaseResourceManger::NextPhase() {
    if (static_cast<int>(m_Phase) >= 30) return;

    m_Phase = m_Phase + 1;
}