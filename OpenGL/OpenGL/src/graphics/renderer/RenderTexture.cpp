//
//  RenderTexture.cpp
//  OpenGL-mac
//
//  Created by machenfei on 2019/2/3.
//  Copyright © 2019 Jack. All rights reserved.
//

#include "RenderTexture.h"
#include <GL/glew.h>
#include "stb_image_write.h"

extern int stbi__flip_vertically_on_write;

RenderTexture::RenderTexture(int width, int height)
:m_Width(width), m_Height(height)
{
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureId, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "framebuffer complete" << std::endl;
    } else {
        std::cout << "framebuffer uncomplete" << std::endl;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
};

RenderTexture::~RenderTexture()
{
    glDeleteFramebuffers(1, &m_FBO);
}

void RenderTexture::begin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
}

void RenderTexture::end()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::saveToFile(String filename)
{
    char pixels[m_Width * m_Height * 4];
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    stbi__flip_vertically_on_write = 1;
    stbi_write_png(filename.c_str(), m_Width, m_Height, 4, pixels, 4 * m_Width);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
