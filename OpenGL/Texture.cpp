#include "Texture.h"

int Textureshape(const char* SourceTexture, int height, int width, int Channels, bool flip)
{
    //Uses the Stbi image loader to get the file, it's height, width and the amount of colour chanels
    unsigned char* TexturePath = stbi_load(SourceTexture, &width, &height, &Channels, 0);
    //If parameter is met, will flip the texture vertically
    stbi_set_flip_vertically_on_load(flip);
    //generates the texture
    glGenTextures(1, &Texture);
    //binds it
    glBindTexture(GL_TEXTURE_2D, Texture);
    //gets the parameters that the texture will use, including mipmap data
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //if the path is valid
    if (TexturePath)
    {
        //Creates the texture to the desired width, height, colouration and path
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexturePath);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    //Throws an error otherwise
    else
    {
        cout << "ERROR: TEXTURE FAILURE" << endl;
    }
    //removes texture, freeing up space
    stbi_image_free(TexturePath);

    return 0;
}