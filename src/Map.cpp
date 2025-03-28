#include "Map.hpp"

Map::Map(float x, float y, const std::string& texturePath, bool isObstacle)
    : x(x), y(y), obstacleFlag(isObstacle) {
    m_Drawable = TextureManager::GetTexture(texturePath);
    SetPosition({x, y});
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3{x, y, 0.0f});
    modelMatrix = glm::scale(modelMatrix, glm::vec3{1.0f, -1.0f, 1.0f}); // 修正 y 軸翻轉
}



bool Map::isObstacle() const {
    return obstacleFlag;
}
