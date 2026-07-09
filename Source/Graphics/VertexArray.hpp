#pragma once
#include<glad/glad.h>
namespace PixelDome
{
	class VertexArray
	{
	private:
		unsigned int _vertexArray;
	public:
		VertexArray();
		~VertexArray();
		void Bind();
		void UnBind();
		void EnableAttribute(GLuint index);
		void AttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	};
}