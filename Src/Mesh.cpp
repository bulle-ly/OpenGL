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
	m_VertexBuffer = std::make_unique<VertexBuffer>(&vertices[0],this->vertices.size()*sizeof(Vertex));
	m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
	m_VertexBufferLayout->Push<float>(3);//顶点
	m_VertexBufferLayout->Push<float>(3);//法线
	m_VertexBufferLayout->Push<float>(2);//纹理坐标

	m_VAO->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
	m_IBO = std::make_unique<IndexBuffer>(&indices[0],this->indices.size());
	m_Shader = std::make_unique<Shader>("res/Shader/Shader.shader");

	
}


