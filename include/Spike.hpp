//
// Created by USER on 2025/6/5.
//

#ifndef HELLTAKER_SPIKE_HPP
#define HELLTAKER_SPIKE_HPP

#include "AnimatedCharacter.hpp"

enum class SpikeType {
    Static,
    Toggle
};


class Spike : public AnimatedCharacter {
public:
    Spike(const std::vector<std::string>& activeAnimation,
          const std::vector<std::string>& inactiveAnimation,
          SpikeType type,
          int toggleInterval = 1);

    void OnStep();
    bool IsActive() const;
    void SetAlwaysActive(bool active);

private:
    void UpdateAnimation();

    std::vector<std::string> m_ActiveAnim;
    std::vector<std::string> m_InactiveAnim;
    SpikeType m_Type;
    int m_ToggleInterval;
    int m_CurrentSteps;
    bool m_IsActive;
};

#endif //HELLTAKER_SPIKE_HPP
