#pragma once
#include<iostream>
#include<string>
#include<string_view>
#include<fstream>
#include<sstream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
namespace PixelDome
{
	class Shader
	{
	private:
		unsigned int _program;
		std::string LoadFromFile(std::string_view path);
		unsigned int Compile(unsigned int type, const std::string& source);
	public:
		Shader(std::string_view vertexPath, std::string_view fragmentPath);
		~Shader();
		Shader(const PixelDome::Shader& shader) = delete;
		PixelDome::Shader& operator=(const PixelDome::Shader& shader) = delete;
		Shader(PixelDome::Shader&& other) noexcept;
		PixelDome::Shader& operator=(PixelDome::Shader&& other) noexcept;
		void Use();
		void UnUse();
		void SetMat4(std::string_view name, const glm::mat4& value);
		void SetFloat(std::string_view name, float value);
	};
}