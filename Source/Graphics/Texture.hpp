#pragma once
#include<iostream>
#include<string>
#include<string_view>
#include<glad/glad.h>
#include<stb_image.h>
namespace PixelDome
{
	class Texture
	{
	private:
		unsigned int _texture;
	public:
		Texture(std::string_view path);
		~Texture();
		Texture(const PixelDome::Texture&) = delete;
		PixelDome::Texture& operator=(const PixelDome::Texture&) = delete;
		Texture(PixelDome::Texture&& other) noexcept;
		PixelDome::Texture& operator=(PixelDome::Texture&& other) noexcept;
		void Bind();
		void UnBind();
		unsigned int GetTexture() const;
	};
}