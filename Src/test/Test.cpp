#include "Test.h"
#include"Imgui/imgui.h"
namespace test
{
	TestMeau::TestMeau(Test*& currentTestPointer)
		:m_CurrentTest(currentTestPointer)
	{
	}

	void TestMeau::OnUpdate(float deltaTime)
	{
	}

	void TestMeau::OnRender()
	{
	}

	void TestMeau::OnImguiRender()
	{
		for (auto& test : m_Test)
		{
			if(ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();//在这里调用了创建  实际上在点击按钮之后才创建出类来 
			}
		}
	}

}

