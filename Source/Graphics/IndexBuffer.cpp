#include"IndexBuffer.hpp"
PixelDome::IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &_indexBuffer);
}
PixelDome::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &_indexBuffer);
}
void PixelDome::IndexBuffer::Bind(GLenum target)
{
	glBindBuffer(target, _indexBuffer);
}
void PixelDome::IndexBuffer::UnBind(GLenum target)
{
	glBindBuffer(target, 0);
}
void PixelDome::IndexBuffer::Data(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData(target, size, data, usage);
}