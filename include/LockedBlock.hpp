//
// Created by USER on 2025/4/25.
//

#ifndef HELLTAKER_LOCKEDBLOCK_H
#define HELLTAKER_LOCKEDBLOCK_H
#pragma once
#include "Map.hpp"

class LockedBlock : public Map {
public:
    LockedBlock(float x, float y, const std::string& texturePath)
            : Map(x, y, texturePath, false) {}  // 設定為障礙物
};
#endif //HELLTAKER_LOCKEDBLOCK_H
