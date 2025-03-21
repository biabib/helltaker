//
// Created by USER on 2025/3/21.
//

#ifndef HELLTAKER_TEXTUREMANAGER_HPP
#define HELLTAKER_TEXTUREMANAGER_HPP
#include "Util/Image.hpp"
#include <unordered_map>

class TextureManager {
public:
    static std::shared_ptr<Util::Image> GetTexture(const std::string& path) {
        if (m_TextureCache.find(path) == m_TextureCache.end()) {
            auto texture = std::make_shared<Util::Image>(path);
            m_TextureCache[path] = texture;
        }
        return m_TextureCache[path];
    }

private:
    static std::unordered_map<std::string, std::shared_ptr<Util::Image>> m_TextureCache;
};
#endif //HELLTAKER_TEXTUREMANAGER_HPP
