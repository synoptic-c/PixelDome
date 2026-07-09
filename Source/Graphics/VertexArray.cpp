#include"VertexArray.hpp"
PixelDome::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vertexArray);
}
PixelDome::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_vertexArray);
}
void PixelDome::VertexArray::Bind()
{
	glBindVertexArray(_vertexArray);
}
void PixelDome::VertexArray::UnBind()
{
	glBindVertexArray(0);
}
void PixelDome::VertexArray::EnableAttribute(GLuint index)
{
	glEnableVertexAttribArray(index);
}
void PixelDome::VertexArray::AttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}