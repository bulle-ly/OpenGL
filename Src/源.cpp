#include<GL/glew.h>
#include<GLFW/glfw3.h>
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
    
  
    //imgui初始化
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true); 
    ImGui::StyleColorsDark();
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    glm::vec3 translationA(100, 100, 0);
    glm::vec3 translationB(200, 200, 0);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
       

        renderer.Clear();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader.Bind();
        {
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);

            glm::mat4 mvp = proj * model;

            // shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            shader.SetUniform1i("u_Texture", 0);
            shader.SetUniformMat4("u_Mvp", mvp);
            renderer.Draw(va, ib, shader);

        }
      
        {
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);

            glm::mat4 mvp = proj * model;

            // shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            shader.SetUniform1i("u_Texture", 0);
            shader.SetUniformMat4("u_Mvp", mvp);
            renderer.Draw(va, ib, shader);

        }
        //glDrawArrays(GL_TRIANGLES, 0, 3);



        if (r > 0.5)
            inscream = -0.5f;
        else inscream = 0.5f;

        r += inscream;

        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");             
        

        ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 640.0f);           
        ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 640.0f);


        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    

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

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
