# OpenGL Idea

## Worksheet 2 - original idea
For this project, I will use knowledge from [LearnOpenGL](https://learnopengl.com/) and [The Nature of code book](https://natureofcode.com/) to create a 3D fire system. You will be able to spawn the fire by pressing s key and move the camera with traditional W/A/S/D keyboard and Mouse controls.

This project, because it uses [LearnOpenGL](https://learnopengl.com/), will be using GLAD and GLFW3, and be in around 5 scripts:

- OpenGL.cpp - This file contains the Main, Along with voids for GLFW inputs and mesh creation

 - FragShader.GLSL - Fragement shader

 - VertexShader.GLSL - Vertex shader

 - main.h - ALl the variables for OpenGL.cpp exist here

I will organise and comment the code, and optimise it using [Nisight](https://developer.nvidia.com/nsight-graphics) and In-built Visual Studio Tools.

## Worksheet 3 - New idea
For this project, I will use knowledge obtained from grey litriture which I have compiled into a [playlist](https://youtube.com/playlist?list=PLNfnoxGFwMBv0gdAmP6JhydVtd30DKilU\&si=KShD\_Idr4KxJmqDR) to create terrain in a Unity scene, along with a waves system utilising a mesh.

This project, because it uses Unity, can use the GL libary Unity offers, though I will use the method outlined in the [playlist](https://youtube.com/playlist?list=PLNfnoxGFwMBv0gdAmP6JhydVtd30DKilU\&si=KShD\_Idr4KxJmqDR).

- Meshvalues.cs - a script with all the values, and the primary way to change said values with the UI prefab

 - MeshFunnyGen.cs - a script that generates the mesh visible in the scene.

 - landVertexShaderGraph.shadergraph - a Shader that will allow the rendering of the Color array in Meshvalues.cs (this is also applicable to waterVertexShaderGraph.shadergraph)

 - Land.mat/Water.mat/pab.mat - Material files used to apply the shader graphs (or an image of Pablo, the current family pet, if you choose pab.mat) 

I will organise and comment the code, and optimise it using [Nisight](https://developer.nvidia.com/nsight-graphics) and In-buit Unity profiler, which works on a similar level to the Profiler to Visual Studio.
