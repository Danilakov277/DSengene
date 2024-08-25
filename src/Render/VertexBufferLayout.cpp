#include "VertexBufferLayout.h"

namespace Renderer {

	VertexBufferLayout::VertexBufferLayout() : m_stride(0)
	{
	}

	void VertexBufferLayout::reserveElements(const size_t count)
	{
		m_layoutElements.reserve(count);
	}

	void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
	{
		m_layoutElements.push_back(VertexBufferLayoutElement{ static_cast<GLint>(count),GL_FLOAT,normalized, count * unsigned int(sizeof(GLfloat)) });
		m_stride += m_layoutElements.back().size;
	}
}