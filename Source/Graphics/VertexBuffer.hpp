#pragma once
#include<glad/glad.h>
namespace PixelDome
{
	class VertexBuffer
	{
	private:
		unsigned int _vertexBuffer;
	public:
		VertexBuffer();
		~VertexBuffer();
		void Bind(GLenum target);
		void UnBind(GLenum target);
		void Data(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	};
}