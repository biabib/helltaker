#include "Map.hpp"

Map::Map(float x, float y, const std::string& texturePath, bool isObstacle)
    : x(x), y(y), obstacleFlag(isObstacle) {
    texture = TextureManager::GetTexture(texturePath);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3{x, y, 0.0f});
    modelMatrix = glm::scale(modelMatrix, glm::vec3{1.0f, -1.0f, 1.0f}); // 修正 y 軸翻轉
}

void Map::draw(Core::Matrices& data) {
    data.m_Model = modelMatrix;
    texture->Draw(data);
}

bool Map::isObstacle() const {
    return obstacleFlag;
}
