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
#include <Mesh.h>
#include <ModelTest.h>


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
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
    //返回-1意味着这个值没有使用过

   
    Renderer renderer;
    
  
    //imgui初始化
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init(glsl_version);
   
   /* glEnable(GL_DEPTH_TEST);*/ // 开启前注意模型位置归到屏幕面前
    test::TestClearColor test;
    test::Test* currentTest = nullptr;//基类指针
    test::TestMeau* testMeau = new test::TestMeau(currentTest);//基类指针指向父类
     currentTest = testMeau;
    testMeau->RegisterTest<test::TestClearColor>("ClearColor");
    testMeau->RegisterTest<test::TestTexture>("Texture");
    testMeau->RegisterTest<test::ModelTest>("Model");
    Renderer renerder;
 
    /* Loop until the user closes the window */
	   //创建相机类
	Camera camera;//使用当前window

	ImGuiIO& io = ImGui::GetIO();
   
    while (!glfwWindowShouldClose(window))
    {
		
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        /* Render here */
        renerder.Clear();
        
       

        renderer.Clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

       
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
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        

        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    

        if (currentTest != testMeau)
            delete testMeau;
        delete  currentTest;

  
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
