#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in Vec3 Color;
layout (location = 2) in Vec2 Texture;

out vec3 vertColour;
out vec2 textureCoord;

void main()
{
    gl_Position = vec4(Pos.x, -Pos.y, Pos.z, 1.0);
    verColour = color;
    textureCoord = Texture;
}