//
// Created by USER on 2025/4/11.
//
#include "MapStorage.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

std::vector<std::vector<int>> MapStorage::LoadMap(const std::string& filePath) {
    std::vector<std::vector<int>> map;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filePath << std::endl;
        return map;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int value;
        while (ss >> value) {
            row.push_back(value);
        }
        if (!row.empty()) {
            map.push_back(row);
        }
    }

    file.close();
    return map;
}
