#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 Texture;

//out vec4 vertColour;
out vec2 textureCoord;

uniform mat4 model, view, projection;
//uniform mat4 transform;

void main()
{
    textureCoord = Texture;
    gl_Position = (model*view*projection) * vec4(Pos, 1.0);
};
