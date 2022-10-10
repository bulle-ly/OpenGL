#pragma once
#include<vector>
#include<functional>
#include<string>
#include<iostream>
namespace test{
	class Test
	{
	private:
		
	public:
		Test() {};
		virtual ~Test() {};

		virtual void	OnUpdate(float deltaTime) {}
		virtual void	OnRender() {}
		virtual void	OnImguiRender() {}

	};

	class TestMeau:public Test
	{
	private:
		Test*& m_CurrentTest;
		std::vector < std::pair<std::string, std::function<Test* ()>>> m_Test;

	public:
		TestMeau(Test*& currentTestPointer);
		template<typename T>
		void	RegisterTest(const std::string& name)
		{
			std::cout << "Create" << name <<std::endl;
			m_Test.push_back(std::make_pair(name, []() {return new T(); }));
			//�����˺���ָ������ʵ����������û��ʵ�ʴ����������ǵȵ�����ָ�뱻���òŻᴴ��
		}

		void	OnUpdate(float deltaTime) override;
		void	OnRender() override;
		void	OnImguiRender() override;


	

	};

}

