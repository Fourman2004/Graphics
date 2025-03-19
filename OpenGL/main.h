#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <GL/gl.h> 
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"

using namespace glm;


// A pointer to the window that will be generated
GLFWwindow* window;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
void callMouse(GLFWwindow* window, double xpos, double ypos)};


typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);

//Unsigned integer's for the vertex shader, fragment shader, the program the shader's attached to, along with the buffers for verticies, indicies and the vertex array
GLuint vertexShader, fragmentShader, shaderProgram, VAO, VBO, EBO;

// Matrix for Translation
mat4 model;

float lastF = currentF;
float deltaT = currentF - lastF;

mat4 view;

//Retrives the key presses the user can do.
void inputProcess(GLFWwindow* window);

void scrollMovement(GLFWwindow* window, double xoffset, double yoffset);


/// <summary>
/// Gets the viewport Size
/// </summary>
/// <param name="window"> - The Window That has been created</param>
/// <param name="width"> - The width of the viewport</param>
/// <param name="height"> -  The height of the viewport</param>
void callbackFramebufferSize(GLFWwindow* window, int width, int height);

//Generates the window used for the project
bool WindowGen();

/// <summary>
/// Creates the Shape by drawing verticies in the window. Passes the data through VBO, VAO and EBO buffers.
/// </summery>
int shapeGen();