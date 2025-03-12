#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <GL/gl.h> 
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"

GLFWwindow* window;
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
unsigned int buffer;
GLuint vertexShader, fragmentShader,shaderProgram, VAO, VBO, EBO;

void inputProcess(GLFWwindow* window);
bool WindowGen();
void callbackFramebufferSize(GLFWwindow* window, int width, int height);
int shapeGen();