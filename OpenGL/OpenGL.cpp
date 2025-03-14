// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Most of this code is taken from https://learnopengl.com/, with some alteration to the variable names.

#include "main.h"


int main(void)
{
    screenW = 800;
    screenH = 600;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    WindowGen();
    shader myshader("VertexShader.glsl", "FragmentShader.glsl");
    Model myModel("SurvivalBackpack.obj", false);
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
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      myshader.use();

      //mat4 projection = perspective((float)radians(90), (float)screenW / (float)screenH, 0.1f, 100.0f);
      view = lookAt(vec3(CamX, 0, CamZ), vec3(0, 0, 0), vec3(0, 1, 0));
      //myshader.setMat4("projection", projection);
      myshader.setMat4("view", view);
      myshader.setMat4("model", Trans);
      myModel.Draw(myshader);
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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += mC_speed * CamFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= mC_speed * CamFront;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += normalize(cross(CamFront,camerUp) * mC_speed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= normalize(cross(CamFront, camerUp) * mC_speed);
}

void callbackFramebufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}




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
}