// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Most of this code is taken from https://learnopengl.com/, with some alteration to the variable names.

#include "../Header/main.h"


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    WindowGen();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    stbi_set_flip_vertically_on_load(false);

    shader myshader(FileSystem::getPath("Shaders/VertexShader.glsl").c_str(), FileSystem::getPath("Shaders/FragmentShader.glsl").c_str());
    glEnable(GL_DEPTH_TEST);
    Model myModel(FileSystem::getPath("Model/backpack.obj"));
    while (!glfwWindowShouldClose(window)) 
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        float lastFrame = currentFrame;
         deltaTime = currentFrame - lastFrame;


      inputProcess(window);

      glClearColor(0.05,0.5,0.5,1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      myshader.use();


      mat4 projection = perspective((float)radians(camera.Zoom), (float)screenW / (float)screenH, 0.1f, 100.0f);
      mat4 view = camera.viewMatrix();
	  myshader.setMat4("projection", projection);
      myshader.setMat4("view", view);

      mat4 model = mat4(1.0f);
      model = translate(model, vec3(0.0f, 0.0f, 0.0f));
      model = scale(model, vec3(1, 1, 1));
      myshader.setMat4("model", model);
      myModel.Draw(myshader);

      glfwSwapBuffers(window);
     glfwPollEvents();
    }

    //Deletes the shaders used
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(myshader.ID);
    glfwTerminate();


    return 0;
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
    glfwSetCursorPosCallback(window, callMouse);
    glfwSetScrollCallback(window, scrollMovement);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return window;
}

void callMouse(GLFWwindow* window, double xpos, double ypos)
{
    float Xposition = static_cast<float>(xpos);
    float Yposition = static_cast<float>(ypos);

    if (mouse)
    {
        lastX = Xposition;
        lastY = Yposition;
        mouse = false;
    }
    float Xoff, Yoff;
    Xoff = Xposition - lastX;
    Yoff = Yposition - lastX;
    lastX = Xposition;
    lastY = Yposition;
    camera.mouseMovement(Xoff, Yoff);
}

void inputProcess(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.updateKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.updateKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.updateKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.updateKeyboard(LEFT, deltaTime);

};