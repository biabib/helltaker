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
    bool obstacleFlag;  // 是否為障礙物

    Map(float x, float y, const std::string& texturePath, bool isObstacle = false);

    void draw(Core::Matrices& data);
    bool isObstacle() const;  // 返回是否為障礙物
    glm::vec2 getPosition() const { return glm::vec2(x, y); }  // 取得地圖格子的座標
};

#endif
