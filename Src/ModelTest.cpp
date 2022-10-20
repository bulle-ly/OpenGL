#include "ModelTest.h"
#include "mesh.h"
#include <iostream>

namespace	test {
	ModelTest::ModelTest(std::string path)

	{
		LoadModel(path);

		m_VertexBuffer = std::make_unique<VertexBuffer>(&meshs[0].vertices[0], meshs[0].vertices.size() * sizeof(Vertex));
		m_IBO = std::make_unique<IndexBuffer>(&meshs[0].indices[0], meshs[0].indices.size());


		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_VertexBufferLayout->Push<float>(3);//顶点
		m_VertexBufferLayout->Push<float>(3);//法线
		m_VertexBufferLayout->Push<float>(2);//纹理坐标

		m_VAO->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		m_Shader = std::make_unique<Shader>("res/Shader/Shader.shader");
	}

	void ModelTest::OnUpdate(float deltaTime)
	{

	}

	void ModelTest::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		Renderer renderer;

		m_Shader->Bind();
		renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
	}

	void ModelTest::OnImguiRender()
	{

	}

	void ModelTest::LoadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* secene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!secene || secene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !secene->mRootNode)
		{
			std::cout << "Error" << importer.GetErrorString();
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
		std::vector<Texture> texture;

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
		//顶点
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int i = 0; i < face.mNumIndices; i++)
			{
				indices.push_back(face.mIndices[i]);
			}
		}

		return Mesh(vertices, indices, texture);

	}


	std::vector<Texture> ModelTest::loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			std::string str1 = str.C_Str();
			Texture texture(str1, (Texture::TextureType)type);
			textures.push_back(texture);
		}
		return textures;
	}
}