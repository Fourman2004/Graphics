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
    stbi_set_flip_vertically_on_load(false);

    shader myshader(FileSystem::getPath("Shaders/VertexShader.glsl").c_str(), FileSystem::getPath("Shaders/FragmentShader.glsl").c_str());
    glEnable(GL_DEPTH_TEST);
    Model myModel(FileSystem::getPath("Model/backpack.obj"));
    while (!glfwWindowShouldClose(window))
    {

      inputProcess(window);
      
      model = mat4(1.0f);
      model = translate(model, vec3(0.0f, 0.0f, 0.0f)); 
      model = scale(model, vec3(1, 1, 1));
      glClearColor(0,0,0,1);
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