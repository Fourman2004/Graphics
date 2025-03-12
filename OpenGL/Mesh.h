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
    vec3 position, normal, texCoords, tangent, bitTangent;
    int m_boneIDs[MAX_BONE_INFLUENCE];
};

struct texture
{

};

class Mesh
{
/// <summary>
/// Creates the Shape by drawing verticies in the window. Passes the data through VBO, VAO and EBO buffers.
/// </summery>
	int MeshGen()
	{
        GLfloat vertices[] = {
            0.5,0.5,0,     1,0,0,  1,1,
            0.5,-0.5,0,    0,1,0,   1,0,
            -0.5,-0.5,0,   0,0,1,   0,0,
            -0.5,0.5,0,    1,1,0,   0,1
        };

        GLuint indices[] = {
            0, 1, 2,
            1, 2, 3,
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        return 0;
	}
};

#endif