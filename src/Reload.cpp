//
// Created by USER on 2025/5/2.
//
#include "Reload.hpp"
#include <memory>

Reload::Reload(const std::vector<std::string>& AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, false, 50, false, 0);
}

bool Reload::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}