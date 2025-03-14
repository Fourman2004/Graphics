#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <GL/gl.h> 
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"
#include "Model.h"

using namespace glm;

// A pointer to the window that will be generated
GLFWwindow* window;


typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);

//Unsigned integer's for the vertex shader, fragment shader, the program the shader's attached to, along with the buffers for verticies, indicies and the vertex array
GLuint vertexShader, fragmentShader, shaderProgram, VAO, VBO, EBO;

unsigned int screenW, screenH;

// Matrix for Translation
mat4 model;
// Matrix for Scaling
mat4 Scal;
// Matrix for Rotating
mat4 Rot;

//Retrives the key presses the user can do.
void inputProcess(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        ProcessKeyboard(FORWARD, deltaT);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        ProcessKeyboard(BACKWARD, deltaT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ProcessKeyboard(RIGHT, deltaT);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ProcessKeyboard(LEFT, deltaT);
};

/// <summary>
/// Gets the viewport Size
/// </summary>
/// <param name="window"> - The Window That has been created</param>
/// <param name="width"> - The width of the viewport</param>
/// <param name="height"> -  The height of the viewport</param>
void callbackFramebufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};

//Generates the window used for the project
bool WindowGen()
{


    if (!glfwInit())
        return false;

    window = glfwCreateWindow(screenW, screenH, "3D fire", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, callbackFramebufferSize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return window;
};

/// <summary>
/// Creates the Shape by drawing verticies in the window. Passes the data through VBO, VAO and EBO buffers.
/// </summery>
int shapeGen()
{

    GLfloat vertices[] = {
     0.5,0.5,0,     1,0,0,  1,1,
     0.5,-0.5,0,    0,1,0,   1,0,
     -0.5,-0.5,0,   0,0,1,   0,0,
     -0.5,0.5,0,    1,1,0,   0,1
    };

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3,
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return 0;
};