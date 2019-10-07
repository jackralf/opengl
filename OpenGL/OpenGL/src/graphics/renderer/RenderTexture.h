//
//  RenderTexture.h
//  OpenGL-mac
//
//  Created by machenfei on 2019/2/3.
//  Copyright © 2019 Jack. All rights reserved.
//

#ifndef RenderTexture_h
#define RenderTexture_h

#include "defines.h"

class RenderTexture
{
public:
    RenderTexture(int width, int height);
    ~RenderTexture();
    
    void begin();
    void end();
    void saveToFile(String filename);
private:
    int m_Width, m_Height;
    unsigned int m_FBO, m_RBO, m_TextureId;
};

#endif /* RenderTexture_h */
