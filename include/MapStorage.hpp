//
// Created by USER on 2025/4/11.
//

#ifndef HELLTAKER_MAPSTORAGE_HPP
#define HELLTAKER_MAPSTORAGE_HPP

#include <vector>
#include <string>

class MapStorage {
public:
    static std::vector<std::vector<int>> LoadMap(const std::string& filePath);
    static std::vector<std::vector<std::vector<int>>> LoadAllMaps(const std::string& folderPath);
};

#endif //HELLTAKER_MAPSTORAGE_HPP
