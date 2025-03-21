#include "AnimatedCharacter.hpp"


AnimatedCharacter::AnimatedCharacter(const std::vector<std::string> &AnimationPaths) {
    m_Drawable = std::make_shared<Util::Animation>(AnimationPaths, true, 60, false, 0);


}

bool AnimatedCharacter::IfAnimationEnds() const {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
        return animation->GetCurrentFrameIndex() == animation->GetFrameCount() - 1;
}

void AnimatedCharacter::Move(int dx, int dy, int maxCols, int maxRows) {
    auto Position = this->GetPosition();
    float newX = Position.x + dx * Map::SIZE;
    float newY = Position.y + dy * Map::SIZE;

    // 計算角色所在的行與列
    int col = static_cast<int>(std::round(newX / Map::SIZE));
    int row = static_cast<int>(std::round(newY / Map::SIZE));

    // 檢查邊界，防止角色移動超出地圖範圍
//    if (col >= 0 && col < maxCols && row >= 0 && row < maxRows) {
        Position.x = newX;
        Position.y = newY;
        this->SetPosition(Position);
    //}
}