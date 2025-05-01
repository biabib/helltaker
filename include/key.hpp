//
// Created by USER on 2025/4/25.
//

#ifndef HELLTAKER_KEY_HPP
#define HELLTAKER_KEY_HPP
#pragma once
#include "AnimatedCharacter.hpp"

class Key : public AnimatedCharacter {
public:
    explicit Key(const std::vector<std::string>& AnimationPaths)
            : AnimatedCharacter(AnimationPaths) {
        SetLooping(true);
        Play(); // 鑰匙常駐播放動畫
    }
};
#endif //HELLTAKER_KEY_HPP
