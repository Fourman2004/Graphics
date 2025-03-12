#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <GL/gl.h> 
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"

// A pointer to the window that will be generated
GLFWwindow* window;


typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);



//Unsigned integer's for the vertex shader, fragment shader, the program the shader's attached to, along with the buffers for verticies, indicies and the vertex array
GLuint vertexShader, fragmentShader,shaderProgram, VAO, VBO, EBO;
/*
// Vector 4 for Translation
vec4 Trans;
// Vector 4 for Scaling
vec4 Scal;
// Vector 4 for Rotating
vec4 Rot;*/

//Retrives the key presses the user can do.
void inputProcess(GLFWwindow* window);

//Generates the window used for the project
bool WindowGen();

/// <summary>
/// Gets the viewport Size
/// </summary>
/// <param name="window"> - The Window That has been created</param>
/// <param name="width"> - The width of the viewport</param>
/// <param name="height"> -  The height of the viewport</param>
void callbackFramebufferSize(GLFWwindow* window, int width, int height);

/// <summary>
/// Creates the Shape by drawing verticies in the window. Passes the data through VBO, VAO and EBO buffers.
/// </summery>
int shapeGen();