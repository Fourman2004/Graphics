#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "glm.hpp"
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Shader.h"


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

GLuint VAO, VBO, EBO;

class Mesh
{
public:

    vector<Vertex> vertices;
    vector<GLuint> indicies;
    vector<texture> textures;

    mesh(vector<Vertex> mvertices, vector<GLuint> mindicies, vector<texture> mtextures)
    {
        {
            this->vertices = mvertices;
            this->indicies = mindicies;
            this->textures = mtextures;

            MeshGen();
        }
    };

    void Draw(Shader& shader);

private:
    /// <summary>
    /// Creates the Mesh by drawing verticies in the window. Passes the data through VBO, VAO and EBO buffers.
    /// </summery>
    void MeshGen();

};
#endif