#include"Texture.hpp"
PixelDome::Texture::Texture(std::string_view path)
	:_texture(0)
{
	int width;
	int height;
	int channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(std::string(path).c_str(), &width, &height, &channels, 0);
	if (data)
	{
		unsigned int format = GL_RGB;
		if (channels == 1)
		{
			format = GL_RED;
		}
		if (channels == 2)
		{
			format = GL_RG;
		}
		if (channels == 3)
		{
			format = GL_RGB;
		}
		if (channels == 4)
		{
			format = GL_RGBA;
		}
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture" << " " << path << std::endl;
	}
}
PixelDome::Texture::~Texture()
{
	if (_texture != 0)
	{
		glDeleteTextures(1, &_texture);
	}
}
PixelDome::Texture::Texture(PixelDome::Texture&& other) noexcept
	: _texture(other._texture)
{
	other._texture = 0;
}
PixelDome::Texture& PixelDome::Texture::operator=(PixelDome::Texture&& other) noexcept
{
	if (this != &other)
	{
		if (_texture != 0)
		{
			glDeleteTextures(1, &_texture);
		}
		_texture = other._texture;
		other._texture = 0;
	}
	return *this;
}
void PixelDome::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
}
void PixelDome::Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
unsigned int PixelDome::Texture::GetTexture() const
{
	return _texture;
}