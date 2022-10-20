#pragma once
#include"Test.h"
#include "glm/glm.hpp"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include <memory.h>


namespace	test {
	class TestTexture:public Test
	{
	private:
		glm::vec3	m_translationA;
		glm::vec3	m_translationB;
		glm::mat4	m_View;
		glm::mat4	m_Proj;
	public:
		TestTexture();
		~TestTexture();

		void	OnUpdate(float deltaTime) override;
		void	OnRender() override;
		void	OnImguiRender() override;

		//void	SetModel(glm::mat4 model);
		//void	SetModel(glm::mat4 model, glm::vec3 translate);
		//void	SetModel(glm::mat4 model, glm::vec3 translate,glm::vec3 scale);
		//void	SetModel(glm::mat4 model, glm::vec3 translate, glm::vec3 scale, glm::mat4 rotate);
	/*	void	SetView(glm::mat4 view);
		void	SetProj(glm::mat4 proj);*/
	private:
		std::unique_ptr<VertexArray>		m_VAO;
		std::unique_ptr <IndexBuffer>		m_IBO;
		std::unique_ptr <Shader>			m_Shader;
		std::unique_ptr<Texture>			m_Texture;
		std::unique_ptr<VertexBuffer>		m_VertexBuffer;
		
	};

}


