#include"Mesh.hpp"
PixelDome::Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<int>& layouts)
{
	_indicesCount = (unsigned int)indices.size();
	int stride = 0;
	for (int layout : layouts)
	{
		stride += layout;
	}
	_vertexArray.Bind();
	_vertexBuffer.Bind(GL_ARRAY_BUFFER);
	_vertexBuffer.Data(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	_indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);
	_indexBuffer.Data(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	int offset = 0;
	for (size_t i = 0; i < layouts.size(); i++)
	{
		_vertexArray.AttribPointer(i, layouts[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		_vertexArray.EnableAttribute(i);
		offset += layouts[i];
	}
	_vertexArray.UnBind();
	_vertexBuffer.UnBind(GL_ARRAY_BUFFER);
}
void PixelDome::Mesh::Draw()
{
	_vertexArray.Bind();
	glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, 0);
}
void PixelDome::Mesh::Bind()
{
	_vertexArray.Bind();
}
void PixelDome::Mesh::UnBind()
{
	_vertexArray.UnBind();
}