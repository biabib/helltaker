#ifndef PHASE_MANGER_HPP
#define PHASE_MANGER_HPP

#include "Util/GameObject.hpp"
#include "TaskText.hpp"
#include "Character.hpp"
#include "Phase.hpp"

class PhaseResourceManger {
public:
    PhaseResourceManger();


    void NextPhase();
    int GetCurrentPhase() const { return m_Phase; }


private:
    int m_Phase = 1;
};


#endif //PHASE_MANGER_HPP
