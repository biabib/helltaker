//
// Created by USER on 2025/4/11.
//
#include "Goal.hpp"

Goal::Goal(const std::vector<std::string> &AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, true, 60, false, 0);

}

bool Goal::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}