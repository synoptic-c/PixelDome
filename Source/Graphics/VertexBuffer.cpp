#include"VertexBuffer.hpp"
PixelDome::VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &_vertexBuffer);
}
PixelDome::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_vertexBuffer);
}
void PixelDome::VertexBuffer::Bind(GLenum target)
{
	glBindBuffer(target, _vertexBuffer);
}
void PixelDome::VertexBuffer::UnBind(GLenum target)
{
	glBindBuffer(target, 0);
}
void PixelDome::VertexBuffer::Data(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}