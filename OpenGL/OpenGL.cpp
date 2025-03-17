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
    Model myModel("Cube.fbx");

    while (!glfwWindowShouldClose(window))
    {

      inputProcess(window);
      
      model = mat4(1.0f);
      model = translate(model, vec3(0.0f, 0.0f, 0.0f)); 
      model = scale(model, vec3(1, 1, 1));
      glClearColor(1,1,1,1);
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

/*int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    WindowGen();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    shader ourShader("VertexShader.glsl", "Fragmentshader.glsl");
    // load models
    // -----------
    Model ourModel("../Model/PabloTower.fbx");


    // draw in wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaT = currentFrame - lastF;
        lastF = currentFrame;

        // input
        // -----
        inputProcess(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenW / (float)screenH, 0.1f, 100.0f);
        view = camera.viewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}*/