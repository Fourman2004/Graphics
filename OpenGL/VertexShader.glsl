#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 Texture;

out vec4 vertColour;
out vec2 textureCoord;

void main()
{
    gl_Position = vec4(Pos.x, Pos.y, Pos.z, 1.0);
    vertColour = Color;
    textureCoord = vec2(Texture.x, Texture.y);
};
