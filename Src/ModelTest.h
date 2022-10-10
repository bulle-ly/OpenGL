#pragma once
#include <assimp/config.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h> 
#include <string>
#include <vector>
class ModelTest
{
public:
	
	ModelTest(std::string FileName);
private:
	std::string Directory;
	std::vector<Mesh> meshs;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

