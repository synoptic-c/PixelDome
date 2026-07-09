#pragma once
#include<vector>
#include<cstddef>
#include<glad/glad.h>
#include"Graphics/VertexArray.hpp"
#include"Graphics/VertexBuffer.hpp"
#include"Graphics/IndexBuffer.hpp"
namespace PixelDome
{
	class Mesh
	{
	private:
		VertexArray _vertexArray;
		VertexBuffer _vertexBuffer;
		IndexBuffer _indexBuffer;
		unsigned int _indicesCount;
	public:
		Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<int>& layouts);
		void Draw();
		void Bind();
		void UnBind();
	};
}