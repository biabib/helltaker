#ifndef MAP_HPP
#define MAP_HPP
#include "Util/Image.hpp"
#include "TextureManager.hpp"

class Map {
public:
    std::shared_ptr<Util::Image> texture;
    float x, y;
    static constexpr float SIZE = 100.0f;
    glm::mat4 modelMatrix;

    Map(float x, float y, const std::string& texturePath)
            : x(x), y(y) {
        texture = TextureManager::GetTexture(texturePath);

        // 直接使用傳入的世界座標
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3{x, y, 0.0f});
        modelMatrix = glm::scale(modelMatrix, glm::vec3{1.0f, -1.0f, 1.0f}); // 修正 y 軸翻轉
    }

    void draw(Core::Matrices& data) {
        data.m_Model = modelMatrix;
        texture->Draw(data);
    }
};
#endif