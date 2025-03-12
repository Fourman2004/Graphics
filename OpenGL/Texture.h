#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int Texture;

using namespace std;
int Textureshape(const char* SourceTexture, int height, int width, int Channels)
{
    unsigned char *TexturePath = stbi_load(SourceTexture, &width, &height, &Channels, 0);
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (TexturePath)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexturePath);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "ERROR: TEXTURE FAILURE" << endl;
    }
    stbi_image_free(TexturePath);

    return 0;
}