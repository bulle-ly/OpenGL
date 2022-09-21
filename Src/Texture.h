#pragma once

#include"Renderer.h"
class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(std::string FileName);
	~Texture();

	void Bind(unsigned int slot = 0)const;
	void UnBind()const;

};

