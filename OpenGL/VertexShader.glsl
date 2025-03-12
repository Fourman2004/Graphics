#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 Texture;

out vec2 textureCoord;

uniform mat4 model, view, projection;

void main()
{
    gl_Position = (model * view * projection) * vec4(Pos.x, Pos.y, Pos.z, 1.0);
    textureCoord = Texture;
};
