#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/// <summary>
/// <para>Shader Class that grabs the GLSL files.</para>
/// <para>performs checks to see if Both Vertex and Fragment shader's are valid and operational</para>
/// <para>It will then Apply the shaders to a buffer via Buffers</para>
/// <para></para>
/// </summary>
class shader
{
public:

	//Program ID. It will allow the shaders to link up to the main script when the function is called
	unsigned int ID;

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
	shader(const char* VertexShader, const char* FragmentShader)
	{
		//string is for the code inside the files
		string vCode, fCode;
		//ifstream is for the file path.
		ifstream vFile, fFile;
		vFile.exceptions(ifstream::failbit || ifstream::badbit);
		fFile.exceptions(ifstream::failbit || ifstream::badbit);
		//attempts the following in this order:
		/*
		Opens the Shader Files
		gets a pointer of the files, with the contents of the file
		Sets the string values above to the contents of the now closed files
		*/
		try
		{
			//open the sahder files
			vFile.open(VertexShader);
			fFile.open(FragmentShader);
			//stringstream read/writes the open file into 
			stringstream vStream, fStream;
			//stringstream contains a pointer to the files and their contents
			vStream << vFile.rdbuf();
			fStream << fFile.rdbuf();
			//closes the shader files
			vFile.close();
			fFile.close();
			//string files are equal to the content and pointer now held in the stringstream.
			vCode = vStream.str();
			fCode = fStream.str();
		}
		//If it can't, it will display an error message saying what went wrong.
		catch(ifstream::failure& flaw)
		{
			cout << "ERROR WITH FILE:" << flaw.what() << endl;
		}
		//Creates a constant pointer which will contain the yet unexecuted shaders
		const char* vShadCode;
		const char* fShadCode;
		//sets the pointers to the shader code
		vShadCode = vCode.c_str();
		fShadCode = fCode.c_str();
		GLuint V, F;
		//Creates the vertex shader and applies it to the unsigned integer V.
		//It will then set or replace the old shader code with new code, and executes it
		//Finally, it compiles
		V = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(V,1,&vShadCode,NULL);
		glCompileShader(V);
		//checks to see if it's compiled properly
		errorCheck(V, "Vertex");
		//Creates the Fragment shader and applies it to the unsigned integer F.
		//It will then set or replace the old shader code with new code, and executes it
		//Finally, it compiles
		F = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(F, 1, &fShadCode, NULL);
		glCompileShader(F);
		//checks to see if it compiled properly
		errorCheck(F, "Fragment");
		//Creates the Program and applies it to the unsigned integer ID.
		//It will Attach V and F to the the 
		//Finally, it links
		ID = glCreateProgram();
		glAttachShader(ID, V);
		glAttachShader(ID, F);
		glLinkProgram(ID);
		//checks to see if the ID linked properly
		errorCheck(ID, "Program");
		//Removes the data for the shaders, freeing up memory
		glDeleteShader(V);
		glDeleteShader(F);
	}
	//Uses the shaders attached to the ID
	void use()
	{
		glUseProgram(ID);
	}
	//If a uniform bool is used, it will set the bool to the value
	void setBoolValue(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	//If a uniform Integer is used, it will set the int to the value
	void setIntValue(const string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	//If a uniform Float is used, it will set the float to the value
	void setFloatValue(const string& name, float value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
private:
	/// <summary>
	/// This function is called whenever a shader is created and passed through the buffers.
	/// If it's called and the compiler doesn't find anything successful about the shaders. It will throw an error stating what is wrong.
	/// It will continually do this until the program is exited out of or it stops running for one reason or another.
	/// </summary>
	/// <param name="shader"> - What shader it is, and will decide what error message to throw. Returns the failure of the variables "V" ,"F" or "ID"</param>
	/// <param name="type"> - Basically a tag in engines like unity. It will Print a specific error based on the tag and the shader paramete before it </param>
	void errorCheck(unsigned int shader, string type)
	{
		int success;
		char infolog[1024];
		if (type != "Program")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				cout << "ERROR:" << type << "FAILED TO COMPILE!" << "\n" << infolog << "\n" << "-- --------------------------------------------------- -- " << endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infolog);
				std::cout << "ERROR:" << type << "FAILED TO LINK!" << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};

#endif