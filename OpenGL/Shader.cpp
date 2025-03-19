#include "Shader.h"

Shader shader(const char* VertexShader, const char* FragmentShader)
{
	//string is for the code inside the files
	string vCode, fCode;
	//ifstream is for the file path.
	ifstream vFile, fFile;
	vFile.exceptions(ifstream::failbit | ifstream::badbit);
	fFile.exceptions(ifstream::failbit | ifstream::badbit);
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
	catch (ifstream::failure& flaw)
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
	glShaderSource(V, 1, &vShadCode, NULL);
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

void use()
{
	glUseProgram(ID);
}

void setBool(const string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void setInt(const string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void setFloat(const string& name, float value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void setVec2(const string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void setVec3(const string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void setVec3(const string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void setVec4(const string& name, const vec4& value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void setVec4(const string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void setMat2(const string& name, const mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat3(const string& name, const mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void setMat4(const string& name, const mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

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