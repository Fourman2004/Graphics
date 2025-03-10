#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class shader
{
public:
	unsigned int ID;

	shader(const char* VertexShader, const char* FragmentShader)
	{
		string vCode, fCode;
		ifstream vFile, fFile;
		vFile.exceptions(ifstream::failbit || ifstream::badbit);
		fFile.exceptions(ifstream::failbit || ifstream::badbit);
		try
		{
			vFile.open(VertexShader);
			fFile.open(FragmentShader);
			stringstream vStream, fStream;
			vStream << vFile.rdbuf();
			fStream << fFile.rdbuf();
			vFile.close();
			fFile.close();
			vCode = vStream.str();
			fCode = fStream.str();
		}
		catch(ifstream::failure& flaw)
		{
			cout << "ERROR WITH FILE:" << flaw.what() << endl;
		}
		const char* vShadCode;
		const char* fShadCode;
		vShadCode = vCode.c_str();
		fShadCode = fCode.c_str();
		GLuint V, F;
		V = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(V,1,&vShadCode,NULL);
		glCompileShader(V);
		errorCheck(V, "Vertex");
		F = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(F, 1, &fShadCode, NULL);
		glCompileShader(F);
		errorCheck(F, "Fragment");
		ID = glCreateProgram();
		glAttachShader(ID, V);
		glAttachShader(ID, F);
		glLinkProgram(ID);
		errorCheck(ID, "Program");
		glDeleteShader(V);
		glDeleteShader(F);
	}
	void use()
	{
		glUseProgram(ID);
	}
	void setBoolValue(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setIntValue(const string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloatValue(const string& name, float value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
private:
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