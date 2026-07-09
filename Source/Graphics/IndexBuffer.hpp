#pragma once
#include<glad/glad.h>
namespace PixelDome
{
	class IndexBuffer
	{
	private:
		unsigned int _indexBuffer;
	public:
		IndexBuffer();
		~IndexBuffer();
		void Bind(GLenum target);
		void UnBind(GLenum target);
		void Data(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	};
}