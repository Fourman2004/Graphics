#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "main.h"
#include <fstream>
#include <sstream>


using namespace std;
using namespace glm;

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
	shader(const char* VertexShader, const char* FragmentShader, const char* geometryPath = nullptr)
	{
		//string is for the code inside the files
		string vCode, fCode, gCode;
		//ifstream is for the file path.
		ifstream vFile, fFile, gFile;
		vFile.exceptions(ifstream::failbit || ifstream::badbit);
		fFile.exceptions(ifstream::failbit || ifstream::badbit);
		gFile.exceptions(ifstream::failbit || ifstream::badbit);
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
			stringstream vStream, fStream, gStream;
			//stringstream contains a pointer to the files and their contents
			vStream << vFile.rdbuf();
			fStream << fFile.rdbuf();
			cout << "Vertex Shader Files Loaded" << VertexShader << endl;
			cout << "Fragment Files Loaded" << FragmentShader << endl;
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
		GLuint V, F, G;
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

		if (geometryPath != nullptr)
		{
			const char* gShadCode = gCode.c_str();
			G = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(G, 1, &gShadCode, NULL);
			glCompileShader(G);
			errorCheck(G, "Geometry");
		}
		//
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
		if (geometryPath!= nullptr)
			glDeleteShader(G);
	}
	//Uses the shaders attached to the ID
	void use()
	{
		glUseProgram(ID);
	}
	/// <summary>
	/// If a uniform Float is used, it will set the float to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The bool, either true or false. This is converted into an integer between 0 or 1</param>
	void setBool(const string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	/// <summary>
	/// If a uniform Float is used, it will set the float to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The Integer value in the shader</param>
	void setInt(const string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	/// <summary>
	/// If a uniform Float is used, it will set the float to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// /// <param name="value"> - The Float/Double value in the shader</param>
	void setFloat(const string& name, float value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	/// <summary>
	/// If a uniform 2D is used, it will set the Vector to the value
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The Combined value of X,Y in a 2D vector</param>
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	/// <summary>
	/// Alternative to setVec2()
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="x"> - The X axis of the 2D vector</param>
	/// <param name="y"> - the y axis of the 2D vector</param>
	void setVec2(const string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
	}
	/// <summary>
	/// If a uniform 3D is used, it will set the Vector to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The combined value of X,Y,Z in a 3D vector</param>
	void setVec3(const string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	/// <summary>
	///Alternative to setVec3()
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="x"> - the X axis in the 3D vector</param>
	/// <param name="y"> - the Y axis in the 3D vector</param>
	/// <param name="z"> - the Z axis in the 3D vector</param>
	void setVec3(const string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
	/// <summary>
	/// If a uniform 4D vector is used, it will set the Vector to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="value"> - The combined value of X,Y,Z,W in a 4D vector</param>
	void setVec4(const string& name, const vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}
	/// <summary>
	/// Alternative to setVec4()
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="x"> - the X axis in the 4D vector</param>
	/// <param name="y"> - the Y axis in the 4D vector</param>
	/// <param name="z"> - the Z axis in the 4D vector</param>
	/// <param name="w"> - The divisonary value within the 4D vector</param>
	void setVec4(const string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
	/// <summary>
	///  If a uniform 2D matrix is used, it will set the matricies to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="mat">The Combined value of a 2D matrix</param>
	void setMat2(const string& name, const mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	/// <summary>
	///  If a uniform 3D matrix is used, it will set the matricies to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="mat">The Combined value of a 3D matrix</param>
	void setMat3(const string& name, const mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	/// <summary>
	///  If a uniform 4D matrix is used, it will set the matricies to the value
	/// </summary>
	/// <param name="name"> - Name of the Shader Variable</param>
	/// <param name="mat">The Combined value of a 4D matrix</param>
	void setMat4(const string& name, const mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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