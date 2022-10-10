#include "TestTexture.h"
#include"Renderer.h"
#include"Imgui/imgui.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
namespace test {
	TestTexture::TestTexture()
		:m_translationA(200, 200, 0), m_translationB(400, 200, 0),
		m_Proj(glm::ortho(0.0f, 640.0f, 0.f, 480.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Model(glm::mat4(1.0f))
	{		
		
		
		float positions[] = {
	   -250.0f,-250.0f,0.0f,0.0f,
		250.0f,-250.0f,1.0f,0.0f,
		250.0f, 250.0f,1.0f,1.0f,
	   -250.0f, 250.0f,0.0f,1.0f
		};

		unsigned int indecies[] =
		{
			0,1,2,
			2,3,0
		};

		m_VAO = std::make_unique<VertexArray>();
		
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		
		m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
		m_VertexBufferLayout->Push<float>(2);
		m_VertexBufferLayout->Push<float>(2);
		
		m_VAO->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

		m_IBO = std::make_unique<IndexBuffer>(indecies, 6);

		m_Texture = std::make_unique<Texture>("res/Texture/Snow.jpg");
		
		m_Shader = std::make_unique<Shader>("res/Shader/Shader.shader");
		
		m_Shader->Bind();
		//m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
		


	}
	TestTexture::~TestTexture()
	{

	}
	void TestTexture::OnUpdate(float deltaTime)
	{

	}
	void TestTexture::OnRender()
	{
		GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->Bind();
		{
			m_Model = glm::translate(glm::mat4(1.0f), m_translationA);
			glm::mat4	mvp = m_Proj * m_View * m_Model;
			m_Shader->Bind();
			m_Shader->SetUniform1i("u_Texture", 0);
			m_Shader->SetUniformMat4("u_Mvp", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
			glm::mat4	mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniform1i("u_Texture", 0);
			m_Shader->SetUniformMat4("u_Mvp", mvp);
			renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
		}
	}

	void TestTexture::OnImguiRender()
	{

		ImGui::SliderFloat3("TranslationA", &m_translationA.x, 0.0f, 640.0f);
		ImGui::SliderFloat3("TranslationB", &m_translationB.x, 0.0f, 640.0f);
		/*float color[4] = { 0.3f,0.3f,0.5f,1.0f };
		ImGui::ColorEdit4("Clear Color", color);*/
	}
	//
	//void TestTexture::SetModel(glm::mat4 model)
	//{	
	//	m_Model = model;
	//}

	//void TestTexture::SetModel(glm::mat4 model, glm::vec3 translate)
	//{

	//}

	//void TestTexture::SetModel(glm::mat4 model, glm::vec3 translate, glm::vec3 scale)
	//{

	//}

	//void TestTexture::SetModel(glm::mat4 model, glm::vec3 translate, glm::vec3 scale, glm::mat4 rotate)
	//{

	//}

	//void TestTexture::SetView(glm::mat4 view)
	//{
	//	m_View = view;
	//}

	/*void TestTexture::SetProj(glm::mat4 proj)
	{
		m_Proj = proj;
	}*/

}

