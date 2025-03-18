#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "main.h"


#define MAX_BONE_INFLUENCE 4

using namespace glm;
using namespace std;

struct Vertex
{
    vec3 position, normal, tangent, bitTangent;
    vec2 texCoords;
    int m_boneIDs[MAX_BONE_INFLUENCE];
    float weight[MAX_BONE_INFLUENCE];
};

struct texture
{
    GLuint id;
    string type,path;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indicies;
    vector<texture> textures;
    GLuint VAO, VBO, EBO;

    Mesh(vector<Vertex> vertices, vector<GLuint> indicies, vector<texture> textures)
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
        diffuse = 0;
        specular = 0;
        for (GLuint i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse") {
                number = to_string(diffuse++);
            }
            else if (name == "texture_specular") {
                number = to_string(specular++);
            }
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);

        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLuint>(indicies.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        shader.use();
        glActiveTexture(GL_TEXTURE0);
    };
private:

    //Unsigned integer's for the vertex shader, fragment shader, the program the shader's attached to, along with the buffers for verticies, indicies and the vertex array

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
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indicies.size(), indicies.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,tangent));
    
        
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitTangent));
        glEnableVertexAttribArray(4);

       
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_boneIDs));
        glEnableVertexAttribArray(5);
   
        
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weight));
        glEnableVertexAttribArray(6);

        glBindVertexArray(0);
	}
};


#endif