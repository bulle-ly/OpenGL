#include "Mesh.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> texture)
	:m_Proj(glm::ortho(0.0f, 640.0f, 0.f, 480.0f, -1.0f, 1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;
	
	this->setupMesh();
}

void Mesh::setupMesh()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(&vertices[0],this->vertices.size()*sizeof(Vertex));
	m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
	m_VertexBufferLayout->Push<float>(3);//顶点
	m_VertexBufferLayout->Push<float>(3);//法线
	m_VertexBufferLayout->Push<float>(2);//纹理坐标

	m_VAO->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
	m_IBO = std::make_unique<IndexBuffer>(&indices[0],this->indices.size());
	m_Shader = std::make_unique<Shader>("res/Shader/ModelShader.shader");
	
	
}

void Mesh::Draw()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	Renderer renderer;
	
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.5, 0.5, 0.5, 0.5);
	
	glm::mat4 Model = glm::translate(glm::mat4(1.0f), m_translationA);
	glm::mat4 mvp = m_Proj * m_View * Model;

	m_Shader->SetUniformMat4("u_Mvp", mvp);
	
	renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
}

