#include "VertexArray.h"
#include"VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{ 
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer( VertexBuffer& vb, VertexBufferLayout& layuot)
{
	Bind();
	vb.BindBuffer();
	unsigned int offset = 0;

	const auto& elements = layuot.GetElement();
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layuot.GetStride(),(const void *)offset));
	
		offset += element.count*VertexBufferLayoutElement::GetSizeOfType(element.type);
	}
}	

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
