#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "main.h"


#define MAX_BONE_INFLUENCE

using namespace glm;
using namespace std;

struct Vertex
{
    vec3 position, normal, tangent, bitTangent;
    vec2 texCoords;
    int m_boneIDs[MAX_BONE_INFLUENCE];
};

struct texture
{
    unsigned int id;
    string type,path;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indicies;
    vector<texture> textures;
    Mesh(vector<Vertex> vertices, vector<unsigned int> indicies, vector<texture> textures)
    {
        {
            this->vertices = vertices;
            this->indicies = indicies;
            this->textures = textures;

            MeshGen();
        }
    };
    void Draw(shader &shader)
    {
        GLuint diffuse, specular;
        diffuse = 1;
        specular = 1;
        for (GLuint i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse") { number = to_string(diffuse++);}
            else if("tesxture_specular") { number = to_string(specular++);}
            shader.setInt(("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    };
private:

    //Unsigned integer's for the vertex shader, fragment shader, the program the shader's attached to, along with the buffers for verticies, indicies and the vertex array
    GLuint VAO, VBO, EBO;


/// <summary>
/// Creates the Mesh by drawing verticies in the window. Passes the data through VBO, VAO and EBO buffers.
/// </summery>
	void MeshGen()
	{

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), &indicies[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertex), (void*)offsetof(Vertex,normal));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertex), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(Vertex), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
	}
};

#endif