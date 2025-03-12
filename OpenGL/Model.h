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
	vector<texture> L_textures;
	vector<Mesh> meshes;
	string dir;
	bool gamma;
	Model(const char* path, bool gammaCorrect = false) : gamma(gammaCorrect)
	{
		loadModel(path);
	};
	void Draw(shader& shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++) { meshes[i].Draw(shader); }
	};
private:

	void loadModel(string path)
	{
		Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ASSIMP ERROR!:" << importer.GetErrorString() << endl;
			return;
		}
		dir = path.substr(0, path.find_last_of("/"));
		processNode(scene->mRootNode, scene);
	};
	void processNode(aiNode* node, const aiScene* scene)
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
	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> verticies;
		vector<GLuint> indicies;
		vector<texture> textures;
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
			}
			if (mesh->mTextureCoords[0])
			{
				vec2 vector2;
				vector2.x = mesh->mTextureCoords[0][i].x;
				vector2.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoords = vector2;
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.tangent = vector;
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.bitTangent = vector;
			}
			else
			{
				vertex.texCoords = vec2(0, 0);
			}
			verticies.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indicies.push_back(face.mIndices[j]);
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<texture> diffuseMaps = loadedTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<texture> specularMaps = loadedTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<texture> normalMaps = loadedTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<texture> heightMaps = loadedTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		return Mesh(verticies, indicies, textures);
	};
	vector<texture> loadedTextures(aiMaterial* material, aiTextureType texType, string typeName)
	{
		vector<texture> textures;
		for (unsigned int i = 0; i < material->GetTextureCount(texType); i++)
		{
			aiString texStr;
			material->GetTexture(texType, i, &texStr);
			bool skip = false;
			for (unsigned int j = 0; j < L_textures.size(); j++)
			{
				if (strcmp(L_textures[j].path.data(), texStr.C_Str()) == 0)
				{
					textures.push_back(L_textures[j]);
					skip = true;
					break;
				}
				if (!skip)
				{
					texture texture;
					texture.id = TextureFromFile(texStr.C_Str(), dir, gamma);
					texture.type = typeName;
					texture.path = texStr.C_Str();
					textures.push_back(texture);
					L_textures.push_back(texture);
				}
				return textures;
			}
		}
	};
	unsigned int TextureFromFile(const char* path, const string& directory, bool gamma)
	{
		string textureFIle = string(path);
		textureFIle = dir + "/" + textureFIle;
		unsigned int texID;
		glGenTextures(1, &texID);
		int width, height, compnumber;
		unsigned char* data = stbi_load(textureFIle.c_str(), &width, &height, &compnumber, 0);
		if (data)
		{
			GLenum format;
			if (compnumber == 1) { format = GL_RED; }
			else if (compnumber == 3) { format = GL_RGB; }
			else if (compnumber == 4) { format = GL_RGBA; }

			glBindTexture(GL_TEXTURE_2D, texID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			stbi_image_free(data);
		}
		else
		{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
		}

		return texID;
	};
};
#endif
