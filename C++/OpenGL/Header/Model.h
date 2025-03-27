#pragma once
#ifndef MODEL_H
#define MODEL_H
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "../ufbx.h"

struct Vertex {
    ufbx_vec3 position;
    ufbx_vec3 normal;
    ufbx_vec2 uv;
};

void convert_mesh_part(ufbx_mesh* mesh, ufbx_mesh_part* part)
{
    vector<Vertex> vertices;
    vector<GLuint> indices;
    indices.resize(mesh->max_face_triangles * 3);

    // Iterate over each face using the specific material.
    for (uint32_t face_index : part->face_indices) {
        ufbx_face face = mesh->faces[face_index];

        // Triangulate the face into `tri_indices[]`.
        uint32_t num_tris = ufbx_triangulate_face(
            indices.data(), indices.size(), mesh, face);

        // Iterate over each triangle corner contiguously.
        for (size_t i = 0; i < num_tris * 3; i++) {
            uint32_t index = indices[i];

            Vertex v;
            v.position = mesh->vertex_position[index];
            v.normal = mesh->vertex_normal[index];
            v.uv = mesh->vertex_uv[index];
            vertices.push_back(v);
        }
    }

    // Should have written all the vertices.
    assert(vertices.size() == part->num_triangles * 3);

    // Generate the index buffer.
    ufbx_vertex_stream streams[1] = {
        { vertices.data(), vertices.size(), sizeof(Vertex) },
    };
    std::vector<uint32_t> indices;
    indices.resize(part->num_triangles * 3);

    // This call will deduplicate vertices, modifying the arrays passed in `streams[]`,
    // indices are written in `indices[]` and the number of unique vertices is returned.
    size_t num_vertices = ufbx_generate_indices(
        streams, 1, indices.data(), indices.size(), nullptr, nullptr);

    // Trim to only unique vertices.
    vertices.resize(num_vertices);

    create_vertex_buffer(vertices.data(), vertices.size());
    create_index_buffer(indices.data(), indices.size());
}

#endif
