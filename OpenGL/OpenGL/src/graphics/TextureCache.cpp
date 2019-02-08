//
//  TextureCache.cpp
//  OpenGL-mac
//
//  Created by machenfei on 2019/2/8.
//  Copyright © 2019 Jack. All rights reserved.
//

#include "TextureCache.h"
#include "Texture.h"

TextureCache* TextureCache::_instance = nullptr;
TextureCache::TextureCache()
{
    
}

TextureCache::~TextureCache()
{
    
}

void TextureCache::purge()
{
    for(auto& it : m_TextureMap) {
        delete it.second;
    }
    m_TextureMap.clear();
}

void TextureCache::print()
{
    std::cout << "========= TextureCache info ==========" << std::endl;
    for(auto& it : m_TextureMap) {
        std::cout << it.first << ":" << it.second->getTextureId() << std::endl;
    }
    std::cout << "======================================" << std::endl;
}

Texture* TextureCache::getTexture(String filename)
{
    if(m_TextureMap.find(filename) != m_TextureMap.end()) {
        return m_TextureMap.at(filename);
    }
    
    auto texture = new Texture(filename);
    m_TextureMap[filename] = texture;
    
    return texture;
}
