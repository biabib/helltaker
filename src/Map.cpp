#include "Map.hpp"
#include <fstream>
#include <iostream>

Map::Map(int width, int height) : m_Width(width), m_Height(height) {
    // 初始化二維陣列，預設為 '.'
    m_Tiles = std::vector<std::vector<char>>(height, std::vector<char>(width, '.'));

    // 呼叫 GenerateBorder() 來設置邊界
    GenerateBorder();
}

void Map::GenerateBorder() {
    // 設置四周邊界為 '#'
    for (int y = 0; y < m_Height; ++y) {
        for (int x = 0; x < m_Width; ++x) {
            if (x == 0 || x == m_Width - 1 || y == 0 || y == m_Height - 1) {
                m_Tiles[y][x] = '#';  // 邊界設為 '#'
            }
        }
    }
}

void Map::LoadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "無法開啟地圖檔案：" << filename << std::endl;
        return;
    }

    for (int y = 0; y < m_Height; ++y) {
        for (int x = 0; x < m_Width; ++x) {
            file >> m_Tiles[y][x];
        }
    }
    file.close();

    // 確保四周是邊界
    GenerateBorder();
}

void Map::Render() {
    for (const auto& row : m_Tiles) {
        for (char tile : row) {
            std::cout << tile << ' ';
        }
        std::cout << std::endl;
    }
}

void Map::SetTile(int x, int y, char tile) {
    if (x >= 0 && x < m_Width && y >= 0 && y < m_Height) {
        m_Tiles[y][x] = tile;
    }
}

char Map::GetTile(int x, int y) const {
    if (x >= 0 && x < m_Width && y >= 0 && y < m_Height) {
        return m_Tiles[y][x];
    }
    return ' ';
}
