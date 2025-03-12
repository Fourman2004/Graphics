#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

using namespace Assimp;
using namespace glm;

class Model
{
public:
	Model(char *path)
	{
		loadModel(path);
	};
	void Draw(shader &shader);
	{
		for (unsigned int i = 0; i < meshes.size(); i++) { meshes[i].Draw(shader); }
	}
private:
	vector<Mesh> meshes;
	string dir;
	void loadModel(string path)
	{
		Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene -> mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ASSIMP ERROR!:" << importer.GetErrorString() << endl;
			return;
		}
		dir = path.substr(0, path.find_last_of("/"));
		processNode(scene->mRootNode, scene);
	};
	void processNode(aiNode* node, const aiScene *scene)
	{
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	};
	Mesh processMesh(aiMesh *mesh, const aiScene *scene)
	{
		vector<Vertex> verticies;
		vector<GLuint> indicies;
		vector<texture> textures;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			if (mesh->HasNormals())
			{

			}
			if (mesh->mTextureCoords[0])
			{

			}
			else 
			{
				vertex.texCoords = vec2(0, 0);
			}
			verticies.push_back(vertex);
		}
		
	};
	vector<texture> loadedTextures(aiMaterial *material, aiTextureType texType, string typeName);
};
#endif
