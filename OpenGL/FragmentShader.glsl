#version 330 core

out vec4 FragColor;

in vec2 textureCoord;

uniform sampler2D myTexture_diffuse1;

void main()
{
    FragColor = texture(myTexture_diffuse1, textureCoord);
} 