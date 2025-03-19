#pragma once
#ifndef SHADER_H
#define SHADER_H


#include <iostream>
#include <glad/glad.h>
#include "glm.hpp"
#include <fstream>
#include <sstream>


using namespace std;
using namespace glm;

//Program ID. It will allow the shaders to link up to the main script when the function is called
GLuint ID;


/// <summary>
/// <para>Shader Class that grabs the GLSL files.</para>
/// <para>performs checks to see if Both Vertex and Fragment shader's are valid and operational</para>
/// <para>It will then Apply the shaders to a buffer via Buffers</para>
/// <para></para>
/// </summary>
class Shader
{
public:

	/// <summary>
	/// <para>COnstructor Reads the files that are the parameters</para>
	/// <para>It will then try to apply the shader's to the program</para>
	/// <para>It will throw errors if the parameters are compiling wrong or if it cannot link the program to openGL</para>
	/// <para>Vertex shader files always start with a V</para>
	/// <para>Fragment shader's always start with an F</para>
	/// </summary>
	/// <param name="VertexShader">
	/// <para> - The HLSL/GLSL file that will communicate with this constructor for the vertex shader, and so the verticies in the program. Will contain some input</para>
	/// </param>
	/// <param name="FragmentShader"><para> - The HLSL/GLSL file that will communicate to the individual pixels in the program. can obtain inputs from the Vertex shader</para></param>
	Shader shader(const char* VertexShader, const char* FragmentShader);
	//Uses the shaders attached to the ID
	void use();
	
	/// <summary>
	/// If a uniform Float is used, it will set the float to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The bool, either true or false. This is converted into an integer between 0 or 1</param>
	void setBool(const string& name, bool value) const;

	/// <summary>
	/// If a uniform Float is used, it will set the float to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The Integer value in the shader</param>
	void setInt(const string& name, int value) const;
	/// <summary>
	/// If a uniform Float is used, it will set the float to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// /// <param name="value"> - The Float/Double value in the shader</param>
	void setFloat(const string& name, float value) const;
	/// <summary>
	/// If a uniform 2D is used, it will set the Vector to the value
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The Combined value of X,Y in a 2D vector</param>
	void setVec2(const std::string& name, const glm::vec2& value) const;
	/// <summary>
	/// Alternative to setVec2()
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="x"> - The X axis of the 2D vector</param>
	/// <param name="y"> - the y axis of the 2D vector</param>
	void setVec2(const string& name, float x, float y) const;
	/// <summary>
	/// If a uniform 3D is used, it will set the Vector to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The combined value of X,Y,Z in a 3D vector</param>
	void setVec3(const string& name, const glm::vec3& value) const;
	/// <summary>
	///Alternative to setVec3()
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="x"> - the X axis in the 3D vector</param>
	/// <param name="y"> - the Y axis in the 3D vector</param>
	/// <param name="z"> - the Z axis in the 3D vector</param>
	void setVec3(const string& name, float x, float y, float z) const;
	/// <summary>
	/// If a uniform 4D vector is used, it will set the Vector to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The combined value of X,Y,Z,W in a 4D vector</param>
	void setVec4(const string& name, const vec4& value) const;
	/// <summary>
	/// Alternative to setVec4()
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="x"> - the X axis in the 4D vector</param>
	/// <param name="y"> - the Y axis in the 4D vector</param>
	/// <param name="z"> - the Z axis in the 4D vector</param>
	/// <param name="w"> - The divisonary value within the 4D vector</param>
	void setVec4(const string& name, float x, float y, float z, float w) const;
	/// <summary>
	///  If a uniform 2D matrix is used, it will set the matricies to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="mat">The Combined value of a 2D matrix</param>
	void setMat2(const string& name, const mat2& mat) const;
	/// <summary>
	///  If a uniform 3D matrix is used, it will set the matricies to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="mat">The Combined value of a 3D matrix</param>
	void setMat3(const string& name, const mat3& mat) const;
	/// <summary>
	///  If a uniform 4D matrix is used, it will set the matricies to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="mat">The Combined value of a 4D matrix</param>
	void setMat4(const string& name, const mat4& mat) const;
private:
	/// <summary>
	/// This function is called whenever a shader is created and passed through the buffers.
	/// If it's called and the compiler doesn't find anything successful about the shaders. It will throw an error stating what is wrong.
	/// It will continually do this until the program is exited out of or it stops running for one reason or another.
	/// </summary>
	/// <param name="shader"> - What shader it is, and will decide what error message to throw. Returns the failure of the variables "V" ,"F" or "ID"</param>
	/// <param name="type"> - Basically a tag in engines like unity. It will Print a specific error based on the tag and the shader paramete before it </param>
	void errorCheck(unsigned int shader, string type);
};

#endif