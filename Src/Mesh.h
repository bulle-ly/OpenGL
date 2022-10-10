#pragma once
#include"Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include<vector>
struct  Vertex
{
	glm::vec3	Position;
	glm::vec3	Normal;
	glm::vec2	TexCoord;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices; 
private:
	std::unique_ptr<VertexArray>		m_VAO;
	std::unique_ptr <IndexBuffer>		m_IBO;
	std::unique_ptr <Shader>			m_Shader;
	std::unique_ptr<Texture>			m_Texture;
	std::unique_ptr<VertexBuffer>		m_VertexBuffer;
	std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
};

