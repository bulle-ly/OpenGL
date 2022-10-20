#include "Mesh.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	:m_Proj(glm::ortho(0.0f, 640.0f, 0.f, 480.0f, -1.0f, 1.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{
	
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	
	this->setupMesh();
}

void Mesh::setupMesh()
{
	
	m_VAO = std::make_unique<VertexArray>();
	m_VertexBuffer = std::make_unique<VertexBuffer>(&vertices[0],this->vertices.size()*sizeof(Vertex));
	VertexBufferLayout layout;
	layout.Push<float>(3);//顶点
	layout.Push<float>(3);//法线
	layout.Push<float>(2);//纹理坐标

	m_VAO->AddBuffer(*m_VertexBuffer, layout);
	m_IBO = std::make_unique<IndexBuffer>(&indices[0],this->indices.size());
	m_Shader = std::make_unique<Shader>("res/Shader/ModelShader.shader");
	m_Shader->Bind();
	
}

void Mesh::Draw()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	Renderer renderer;
	
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
	glm::mat4 modelMatrix;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, 45.f, glm::vec3(0.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));

	m_View = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_Proj = glm::perspective(45.0f, (float)920 / (float)780, 0.1f, 1000.0f);
	glm::mat4 Model = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(modelMatrix, 45.f, glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));;

	
	glm::mat4 mvp = m_Proj * m_View * Model;

	m_Shader->SetUniformMat4("u_Mvp", mvp);
	
	renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
}

