#include "ModelTest.h"
#include <iostream>

ModelTest::ModelTest(std::string FileName)
	
{
	LoadModel(FileName);
}

void ModelTest::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* secene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!secene|| secene->mFlags== AI_SCENE_FLAGS_INCOMPLETE || !secene->mRootNode)
	{
		std::cout << "Error" << importer.GetErrorString();
		return;
	}
	this->Directory = path.substr(0, path.find_last_of('/'));
	this->ProcessNode(secene->mRootNode, secene);
}

void ModelTest::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	
		this->meshs.push_back(this->ProcessMesh(mesh, scene));
	}
	for (unsigned int i = 0; i<node->mNumChildren;i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

Mesh ModelTest::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{

}
