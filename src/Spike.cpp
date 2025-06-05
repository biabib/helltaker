//
// Created by USER on 2025/6/5.
//
#include "Spike.hpp"

Spike::Spike(const std::vector<std::string>& activeAnimation,
             const std::vector<std::string>& inactiveAnimation,
             SpikeType type,
             int toggleInterval)
        : AnimatedCharacter(activeAnimation),
          m_ActiveAnim(activeAnimation),
          m_InactiveAnim(inactiveAnimation),
          m_Type(type),
          m_ToggleInterval(toggleInterval),
          m_CurrentSteps(0),
          m_IsActive(true) // 初始為突起
{
}

void Spike::OnStep() {
    if (m_Type == SpikeType::Toggle) {
        m_CurrentSteps++;
        if (m_CurrentSteps >= m_ToggleInterval) {
            m_CurrentSteps = 0;
            m_IsActive = !m_IsActive;
            UpdateAnimation();
        }
    }
}

bool Spike::IsActive() const {
    return m_IsActive;
}

void Spike::SetAlwaysActive(bool active) {
    m_IsActive = active;
    UpdateAnimation();
}

void Spike::UpdateAnimation() {
    if (m_IsActive) {
        SetAnimation(m_ActiveAnim, true);
    } else {
        SetAnimation(m_InactiveAnim, true);
    }
}