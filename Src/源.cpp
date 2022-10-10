#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <opencv2/core/utils/logger.hpp>
#include<opencv2/opencv.hpp>
#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"
#include"Shader.h"
#include"Texture.h"
#include <windows.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"Imgui/imgui.h"
#include"Imgui/imgui_impl_glfw.h"
#include <Imgui/imgui_impl_opengl3.h>

#include<iostream>
#include"GameTimer.h"
#include"test/TestClearColor.h"
#include "test/TestTexture.h"
#include <assimp/config.h>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h> 
#include "Camera.h"


int main()
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1; 

    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
   /* Create a windowed mode window and its OpenGL context */
  

    
    window = glfwCreateWindow(920, 780, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);



    glfwSwapInterval(1);

    if (GLEW_OK != glewInit())
    {
        std::cout << "error";
        return -1;

    }


    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init(glsl_version);
    float x = 20.0f;
    float y = 20.0f;
    glEnable(GL_DEPTH_TEST);
    test::TestClearColor test;
    test::Test* currentTest = nullptr;//基类指针
    test::TestMeau* testMeau = new test::TestMeau(currentTest);//基类指针指向父类
     currentTest = testMeau;
    testMeau->RegisterTest<test::TestClearColor>("ClearColor");
    testMeau->RegisterTest<test::TestTexture>("Texture");
    Renderer renerder;
    /* Loop until the user closes the window */
	   //创建相机类
	Camera camera;//使用当前window

	ImGuiIO& io = ImGui::GetIO();
    
	float LastMousePosX = io.MouseClickedPos->x;
	float LastMousePosY = io.MouseClickedPos->y;
	float xoffset;
	float yoffset;
	float CurMousePosX;
	float CurMousePosY;
    while (!glfwWindowShouldClose(window))
    {
		 CurMousePosX = io.MouseClickedPos->x;
		 CurMousePosY = io.MouseClickedPos->y;
        

         xoffset = CurMousePosX - LastMousePosX;
         yoffset = CurMousePosY - LastMousePosY;
         LastMousePosX = CurMousePosX;
         LastMousePosY = CurMousePosY;
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        /* Render here */
        renerder.Clear();
        
        
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        camera.ProcessMouseMovement(xoffset, yoffset);
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMeau && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMeau;
            }
            currentTest->OnImguiRender();
            ImGui::End();
        }
		
       
        
        ImGui::Render();
      
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */

      
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }
       
        
        
        if (currentTest != testMeau)
            delete testMeau;
        delete  currentTest;
    
    
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
