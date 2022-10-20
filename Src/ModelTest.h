#pragma once
#include <assimp/config.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h> 
#include <string>
#include <vector>
#include "Mesh.h"
#include "test/Test.h"
namespace test {

	class ModelTest :public  Test 
	{
		friend class Mesh;
	public:
		ModelTest(std::string path = "res\\Model\\Bread.stl");
		void	OnUpdate(float deltaTime)override;
		void	OnRender() override;
		void	OnImguiRender() override;
	private:
		std::string Directory;
		std::vector<Mesh> meshs;

		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);

	
	};

}