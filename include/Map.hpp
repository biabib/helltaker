#ifndef MAP_HPP
#define MAP_HPP
#include "Util/Image.hpp"
#include "TextureManager.hpp"
#include "Util/GameObject.hpp"

class Map :public Util::GameObject{
public:
    std::shared_ptr<Util::Image> texture;
    float x, y;
    static constexpr float SIZE = 100.0f;
    glm::mat4 modelMatrix;
    bool obstacleFlag;  // 是否為障礙物

    Map(float x, float y, const std::string& texturePath, bool isObstacle = false);


    bool isObstacle() const;  // 返回是否為障礙物
    [[nodiscard]] glm::vec2 GetPosition() const { return m_Transform.translation; }
    void SetPosition(const glm::vec2& Position) { m_Transform.translation = Position; }
};

#endif
