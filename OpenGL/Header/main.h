#pragma once

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
#include "Camera.h"

using namespace glm;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// A pointer to the window that will be generated
GLFWwindow* window;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float screenW = 800, screenH = 600;
float lastX = screenW/ 2.0f;
float lastY = screenH/ 2.0f;
bool firstMouse = true;

typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);

//Unsigned integer's for the vertex shader, fragment shader, the program the shader's attached to, along with the buffers for verticies, indicies and the vertex array
GLuint vertexShader, fragmentShader, shaderProgram, VAO, VBO, EBO;
float deltaTime, lastFrame;

//Retrives the key presses the user can do.
void inputProcess(GLFWwindow* window);

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

struct Particle
{
	glm::vec3 Position, Velocity;
	glm::vec4 Color;
	float Life;
	Particle()
		: Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) {
	}
};