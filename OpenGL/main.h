#pragma once

#include <iostream>
#include <glad/glad.h>
#include <Shader.h>
#include <GL/gl.h> 
#include <GLFW/glfw3.h>

GLFWwindow* window;
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
unsigned int buffer;
GLuint vertexShader, fragmentShader,shaderProgram, VAO, VBO, EBO;

const char* vertShadSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragShadSource = "out vec4 FragColor;\n "
"void main()\n"
"{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
"}\n";

void inputProcess(GLFWwindow* window);
bool WindowGen();
void callbackFramebufferSize(GLFWwindow* window, int width, int height);
int shapeGen();