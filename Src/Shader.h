#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>

#include"glm/glm.hpp"

struct  ShaderResource
{
    std::string VertexResource;
    std::string FragmentResource;
};
class Shader
{
private:
    std::string m_FileName;
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformLocation;
public:
    Shader(std::string FileName);
    ~Shader();
    
    
    

    void Bind()const;
    void UnBind()const;

    void SetUniform4f(const std::string& Name, float v0, float v1, float v2, float v3);
    void SetUniform1i(const std::string& Name,int value);
    void SetUniform1f(const std::string& Name, int value);
    void SetUniformMat4(const std::string& Name, glm::mat4& Martix);
    
    private:
        int GetUniformlocation(const std::string &Name) const;
		int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
		unsigned int  ComplieShader(unsigned int Type, const std::string& source);
		ShaderResource ParseShader();
};

