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
      //Textureshape("FireTexture.png", 1, 1, 0, true);
      //shapeGen();
      model = glm::mat4(1.0f);
     model = translate(model, vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
      model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      shader myshader("VertexShader.glsl", "FragmentShader.glsl");
      Model myModel("../Model/PabloTower.fbx", false);
      stbi_set_flip_vertically_on_load(true);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glEnable(GL_DEPTH_TEST);
      myshader.use();
      mat4 projection = perspective((float)radians(camera.Zoom), (float)screenW / (float)screenH, 0.1f, 100.0f);
      myshader.setMat4("projection", projection);
      myshader.setMat4("view", view);
      myshader.setMat4("model", model);
      myModel.Draw(myshader);
      /*glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);*/
      glfwSwapBuffers(window);
     glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();


    return 0;
}