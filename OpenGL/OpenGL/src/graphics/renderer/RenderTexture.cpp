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

#define USE_RENDERBUFFER 1


RenderTexture::RenderTexture(int width, int height)
:m_Width(width), m_Height(height)
{
    
#if USE_RENDERBUFFER
    
    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
    
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
#else
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
#endif
};

RenderTexture::~RenderTexture()
{
#if USE_RENDERBUFFER
    glDeleteRenderbuffers(1, &m_RBO);
#else
    glDeleteFramebuffers(1, &m_FBO);
#endif
}

void RenderTexture::begin()
{
#if USE_RENDERBUFFER
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
#else
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
#endif
}

void RenderTexture::end()
{
#if USE_RENDERBUFFER
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
#else
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
}

void RenderTexture::saveToFile(String filename)
{
    char *pixels = (char *)malloc(sizeof(char) * m_Width * m_Height * 4);
    
#if USE_RENDERBUFFER
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
#else
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
#endif
    
    
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    
    stbi__flip_vertically_on_write = 1;
    stbi_write_png(filename.c_str(), m_Width, m_Height, 4, pixels, 4 * m_Width);
    
#if USE_RENDERBUFFER
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
#else
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
    
}
