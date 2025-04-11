//
// Created by USER on 2025/4/11.
//
#include "Enemy.hpp"

Enemy::Enemy(const std::vector<std::string> &AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, true, 60, false, 0);

}

bool Enemy::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}

void Enemy::Move(int dx, int dy, int maxCols, int maxRows) {
    auto Position = this->GetPosition();
    float newX = Position.x + dx * Map::SIZE;
    float newY = Position.y + dy * Map::SIZE;
    Position.x = newX;
    Position.y = newY;
    this->SetPosition(Position);
}