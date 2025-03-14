#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>

class Map {
public:
    Map(int width, int height);  // 建構函數，初始化地圖大小
    void LoadFromFile(const std::string& filename);  // 從檔案載入地圖
    void Render();  // 渲染地圖
    void SetTile(int x, int y, char tile);  // 設定指定座標的地磚
    char GetTile(int x, int y) const;  // 取得指定座標的地磚
    void GenerateBorder();  // 生成地圖邊界

private:
    int m_Width, m_Height;
    std::vector<std::vector<char>> m_Tiles;  // 使用二維陣列存放地磚
};

#endif // MAP_H
