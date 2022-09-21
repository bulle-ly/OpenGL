#include "Renderer.h"
#include<iostream>
void GLClearError()
{
	{
		while (glGetError() != GL_NO_ERROR);
	}
}

bool GLCallLog(const char* Function, const char* file, int line)
{
    {
        while (GLenum error = glGetError())
        {
            std::cout << "Opengl出现错误代码为:" << error << std::endl;
            std::cout << Function << file << line << std::endl;
            return false;
        }
        return true;
    }
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib  , const Shader& shader) const
{
    va.Bind();
    ib.BindBuffer();
    shader.Bind();
    //shader.SetUniform4f("u_Color", 0.3, 0.3, 0.3, 1);
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
