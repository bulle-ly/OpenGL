#pragma once
#include<GL/glew.h>


#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCallLog(#x,__FILE__,__LINE__))

void GLClearError();
bool GLCallLog(const char* Function, const char* file, int line);

class Renderer
{
public:
    void Draw(const VertexArray &va,const IndexBuffer& ib,const Shader& shader)const;
    void Clear( ) const;
private:
};

