#include "Shader.h"
#include"Renderer.h"

Shader::Shader(std::string FileName):
    m_FileName(FileName),m_RendererID(0)
{
    ShaderResource ss;
    ss = ParseShader();
    m_RendererID = CreateShader(ss.VertexResource, ss.FragmentResource);
    
}

Shader::~Shader()
{
    glDeleteShader(m_RendererID);
  
}

int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{

    unsigned int program = glCreateProgram();
    unsigned int vs = ComplieShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = ComplieShader(GL_FRAGMENT_SHADER, FragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    return program;

}

unsigned int Shader::ComplieShader(unsigned int Type, const std::string& source)
{
    unsigned int ID = glCreateShader(Type);
    const char* src = source.c_str();
    glShaderSource(ID, 1, &src, nullptr);
    glCompileShader(ID);

    //TO DO error
    int result;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char) * length);
        glGetShaderInfoLog(ID, length, &length, message);
        std::cout << message << std::endl;
        std::cout << (Type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << std::endl;

        return 0;
    }

    return ID;
}

ShaderResource Shader::ParseShader()
{
    enum  class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(m_FileName);
    std::string line;
    ShaderType Type = ShaderType::NONE;
    std::stringstream ss[2];
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                Type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                Type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)Type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& Name, float v0, float v1, float v2, float v3)
{

    unsigned int location = GetUniformlocation(Name);
    GLCall(glUniform4f(GetUniformlocation(Name), v0, v1, v2, v3));
}

void Shader::SetUniform1i(const std::string& Name, int value)
{
    GLCall(glUniform1i(GetUniformlocation(Name), value));
}

void Shader::SetUniform1f(const std::string& Name, float value)
{
    GLCall(glUniform1f(GetUniformlocation(Name), value));
}

void Shader::SetUniformMat4(const std::string& Name, glm::mat4 &Martix)
{
    GLCall(glUniformMatrix4fv(GetUniformlocation(Name), 1,GL_FALSE,&Martix[0][0]));
}

int Shader::GetUniformlocation(const std::string& Name)const
{
    if (m_UniformLocation.find(Name) != m_UniformLocation.end())
    {
        return m_UniformLocation[Name];
    }
   
    GLint location = glGetUniformLocation(m_RendererID, Name.c_str());
    if (location == -1) 
    {
        std::cout << "shader Location =-1  you can't use it "<<Name<<std::endl;
    }
    else
    {
        m_UniformLocation[Name] = location;
    }
    return m_UniformLocation[Name];
}
