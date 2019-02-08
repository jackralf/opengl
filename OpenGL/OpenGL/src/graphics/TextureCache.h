//
//  TextureCache.h
//  OpenGL-mac
//
//  Created by machenfei on 2019/2/8.
//  Copyright © 2019 Jack. All rights reserved.
//

#ifndef TextureCache_h
#define TextureCache_h

#include "defines.h"
#include<map>

class Texture;
class TextureCache
{
public:
    static TextureCache* getInstance() {
        if(_instance == nullptr) {
            _instance = new TextureCache();
        }
        return _instance;
    }
    
    ~TextureCache();
    void purge();
    void print();
    
    Texture* getTexture(String filename);
    
private:
    TextureCache();
    static TextureCache* _instance;
    
    std::map<String, Texture*> m_TextureMap;
};


#endif /* TextureCache_h */
