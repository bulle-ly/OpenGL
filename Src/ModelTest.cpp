#include "ModelTest.h"
#include "mesh.h"
#include "Imgui/imgui.h"
#include <iostream>

namespace	test {
	ModelTest::ModelTest(std::string path)
	{
		LoadModel(path);
	}

	void ModelTest::OnUpdate(float deltaTime)
	{

	}

	void ModelTest::OnRender()
	{
		
		for (unsigned int i=0;i<meshs.size();i++)
		{
			meshs[i].Draw();
		}
	}
	
	void ModelTest::OnImguiRender()
	{
		ImGui::SliderFloat3("TranslationA", &meshs[0].m_translationA.x, 0.0f, 640.0f);
		ImGui::SliderFloat3("TranslationB", &meshs[0].m_translationB.x, 0.0f, 640.0f);
		for (unsigned int i = 0; i < meshs.size(); i++)
		{
			meshs[i].m_translationA.x = meshs[0].m_translationA.x;
			meshs[i].m_translationB.x = meshs[0].m_translationB.x;
		}
		
	}

	void ModelTest::LoadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* secene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!secene || secene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !secene->mRootNode)
		{
			std::cout << "Error to Load" << importer.GetErrorString();
			return;
		}
		this->Directory = path.substr(0, path.find_last_of('/'));
		this->ProcessNode(secene->mRootNode, secene);
	}

	void ModelTest::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

			this->meshs.push_back(this->ProcessMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			this->ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh ModelTest::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			glm::vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0]->x;
				vec.y = mesh->mTextureCoords[0]->y;
				vertex.TexCoord = vec;
			}
			else
			{
				vertex.TexCoord = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}
		//����
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int i = 0; i < face.mNumIndices; i++)
			{
				indices.push_back(face.mIndices[i]);
			}
		}
		if (mesh->mMaterialIndex>=0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = this->loadMaterialTexture(material,aiTextureType_DIFFUSE);

			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = this->loadMaterialTexture(material, aiTextureType_SPECULAR);

			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		}

		return Mesh(vertices, indices, textures);

	}


	std::vector<Texture> ModelTest::loadMaterialTexture(aiMaterial* mat, aiTextureType type)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			unsigned int id= mat->GetTexture(type, i, &str);
			std::string str1 = str.C_Str();
			Texture texture(str1, (Texture::TextureType)type);
			textures.push_back(texture);
		}
		return textures;
	}
}