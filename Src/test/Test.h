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
			//传入了函数指针所以实际上在这里没有实际创建出来而是等到函数指针被调用才会创建
		}

		void	OnUpdate(float deltaTime) override;
		void	OnRender() override;
		void	OnImguiRender() override;


	

	};

}

