#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
// retrives the textures from the Vertex Shader and applies them accoridngly to the Vector 2.
    FragColor = texture(texture_diffuse1, TexCoords);
}