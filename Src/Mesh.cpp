#include "Mesh.h"



Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> texture)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;
	
	this->setupMesh();
}

void Mesh::setupMesh()
{

}

