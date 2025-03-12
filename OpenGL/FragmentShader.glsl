#version 330 core

out vec4 FragColor;

in vec3 vertColour;
//in vec2 textureCoord;

//uniform sampler2D myTexture;

void main()
{
    FragColor = vertColour;//Texture(myTexture, textureCoord);
} 