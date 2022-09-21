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


#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"Imgui/imgui.h"
#include"Imgui/imgui_impl_glfw.h"
#include <Imgui/imgui_impl_opengl3.h>

#include<iostream>
#include"GameTimer.h"
#include"test/TestClearColor.h"

int main(void)
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
  

    cv::VideoCapture capture(0);

    
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    float positions[] = {
        -50.0f,-50.0f,0.0f,0.0f,
         50.0f,-50.0f,1.0f,0.0f,
         50.0f, 50.0f,1.0f,1.0f,
        -50.0f, 50.0f,0.0f,1.0f
    };

    unsigned int indecies[]=
    {
        0,1,2,
        2,3,0
    };
    //cv::copyTo 浅拷贝 不会共享
    //cv::Mat::zeros

    glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.f, 480.0f, -1.0f, 1.0f);
   
    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push <float>(2);
    layout.Push <float>(2);
    va.AddBuffer(vb, layout);
  

    IndexBuffer  ib(indecies,6);
    
    
    Shader shader("res/Shader/Shader.shader");
    shader.Bind();
   
    Texture tex("res/Texture/Snow.jpg");
    tex.Bind();
    
    
    float r = 1.0f;
    float inscream = 0.05f;
   
    //返回-1意味着这个值没有使用过

    va.UnBind();
    vb.UnBindbuffer();
    ib.UnBindbuffer();
    shader.UnBind();
    Renderer renderer;
    //cv::VideoCapture camera(0);
    //if (camera.isOpened()) {
    //    std::cout << "kaile";
    //    cv::Mat Frame;
    //    camera >> Frame;
    //    cv::imshow("读取视频", Frame);
    //}
    //cv::Mat mat=cv::imread("D:\\ProgramOpencv\\Project1\\Src\\Snow.jpg",1);
    //if (!mat.empty())
    //{
    //    cv::imshow("123", mat);
    //}
    //else
    //{
    //    std::cout << "fail" << std::endl;
    //}
 
    //imgui初始化
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    glm::vec3 translationA(100, 100, 0);
    glm::vec3 translationB(200, 200, 0);
    
    test::TestClearColor test;
    test::Test* currentTest = nullptr;//基类指针
    test::TestMeau* testMeau = new test::TestMeau(currentTest);//基类指针指向父类
    currentTest = testMeau;
    testMeau->RegisterTest<test::TestClearColor>("ClearColor");

    /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
    {
        /* Render here */
         renderer.Clear();
        test.OnRender();
        
        test.OnUpdate(0.0f);
        
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
      
        //shader.Bind();
        //{
        //    
        //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);

        //    glm::mat4 mvp = proj * model;

        //     shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        //    shader.SetUniform1i("u_Texture", 0);
        //    shader.SetUniformMat4("u_Mvp", mvp);
        //    renderer.Draw(va, ib, shader);

        //}
      
        //{
        //    
        //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);

        //    glm::mat4 mvp = proj * model;

        //     shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        //    shader.SetUniform1i("u_Texture", 0);
        //    shader.SetUniformMat4("u_Mvp", mvp);
        //    renderer.Draw(va, ib, shader);

        //}
        //glDrawArrays(GL_TRIANGLES, 0, 3);



        //if (r > 0.5)
        //    inscream = -0.5f;
        //else inscream = 0.5f;

        //r += inscream;

        //static float f = 0.0f;
        //static int counter = 0;

       /* ImGui::Begin("Hello, world!");   */                       // Create a window called "Hello, world!" and append into it.

        //ImGui::Text("This is some useful text.");             
        //

        //ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 640.0f);           
        //ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 640.0f);


        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //    counter++;
        //ImGui::SameLine();
        //ImGui::Text("counter = %d", counter);

        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      /*  ImGui::End();*/
    
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMeau && ImGui::Button("-<"))
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

        va.UnBind();
        vb.UnBindbuffer();
        ib.UnBindbuffer();
        shader.UnBind();
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
    glfwTerminate();
    return 0;
}
