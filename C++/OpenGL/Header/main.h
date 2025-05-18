#pragma once

#include "Camera.h"
#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <GL/gl.h> 
#include "filesystem.h"
#include "LOGLModel.h"
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "Shader.h"

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

using namespace glm;

// A pointer to the window that will be generated
GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

//screen width and height
float screenW = 800, screenH = 600;
//
float lastX = screenW/ 2.0f;
float lastY = screenH/ 2.0f;
//the first instance of the cursor and when it will draw
bool firstMouse = true, Draw = false;

typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);

//Unsigned integer's for the vertex shader, fragment shader, the program the shader's attached to, along with the buffers for verticies, indicies and the vertex array
GLuint vertexShader, fragmentShader, shaderProgram, VAO, VBO, EBO;
//used for Time
float deltaTime, lastFrame;

//Retrives the key presses the user can do.
void inputProcess(GLFWwindow* window);

/// <summary>
/// Retrives the scroll button
/// </summary>
/// <param name="window"> The Open GLFW Window</param>
/// <param name="xoffset"> the X-axis</param>
/// <param name="yoffset"> same as Xoffset but for the Y-axis</param>
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


/// <summary>
/// Gets the viewport Size
/// </summary>
/// <param name="window"> - The Window That has been created</param>
/// <param name="width"> - The width of the viewport</param>
/// <param name="height"> -  The height of the viewport</param>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Generates the window used for the project
bool WindowGen();

/// <summary>
/// Creates the Shape by drawing verticies in the window. Passes the data through VBO, VAO and EBO buffers.
/// </summery>
int shapeGen();
