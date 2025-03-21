//
// Created by USER on 2025/3/21.
//
#include "TextureManager.hpp"

// 這行是必要的！定義 `m_TextureCache`
std::unordered_map<std::string, std::shared_ptr<Util::Image>> TextureManager::m_TextureCache;