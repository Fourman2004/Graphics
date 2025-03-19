// OpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Most of this code is taken from https://learnopengl.com/, with some alteration to the variable names.

#include "main.h"


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    WindowGen();
    //stbi_set_flip_vertically_on_load(false);

    shader myshader("VertexShader.glsl", "FragmentShader.glsl");
    glEnable(GL_DEPTH_TEST);
    Model myModel("Model/Red.fbx");

    while (!glfwWindowShouldClose(window))
    {

      inputProcess(window);
      
      model = mat4(1.0f);
      model = translate(model, vec3(0.0f, 0.0f, 0.0f)); 
      model = scale(model, vec3(1, 1, 1));
      glClearColor(0.5,0.5,0.5,0.5);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      myshader.use();
    
      mat4 projection = perspective((float)radians(camera.Zoom), (float)screenW / (float)screenH, 0.1f, 100.0f);
      view = camera.viewMatrix();
      myshader.setMat4("projection", projection);
      myshader.setMat4("view", view);
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
        camera.updateKeyboard(FORWARD, deltaT);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.updateKeyboard(BACKWARD, deltaT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.updateKeyboard(RIGHT, deltaT);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.updateKeyboard(LEFT, deltaT);

};

void scrollMovement(GLFWwindow* window, double xoffset, double yoffset)
{
    return camera.mouseScroll(static_cast<float>(yoffset));
}

void callbackFramebufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
};

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
};

int shapeGen();
{

    GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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