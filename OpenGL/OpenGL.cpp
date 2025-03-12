// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Most of this code is taken from https://learnopengl.com/, with some alteration to the variable names.

#include "main.h"


int main(void)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    WindowGen();
    //Deletes the shaders used
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
      inputProcess(window);
      Trans = glm::mat4(1.0f);
      Trans = translate(Trans, vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
      Trans = glm::scale(Trans, glm::vec3(1.0f, 1.0f, 1.0f));
      shader myshader("VertexShader.glsl", "FragmentShader.glsl");
      Model Model("Survival_BackPack_2.fbx", true);
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      myshader.use();
      myshader.setMat4("transform", Trans);
      glfwSwapBuffers(window);
     glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();


    return 0;
}

void inputProcess(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void callbackFramebufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}




bool WindowGen()
{


    if (!glfwInit())
        return false;

    window = glfwCreateWindow(800, 600, "3D fire", NULL, NULL);

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
}