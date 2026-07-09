#include"Shader.hpp"
std::string PixelDome::Shader::LoadFromFile(std::string_view path)
{
	std::fstream file(std::string(path), std::ios::in);
	if (!file.is_open())
	{
		std::cout << "Failed to open file" << " " << path << std::endl;
		return "";
	}
	std::string line;
	std::stringstream buffer;
	while (std::getline(file, line))
	{
		buffer << line << "\n";
	}
	file.close();
	return buffer.str();
}
unsigned int PixelDome::Shader::Compile(unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* sourcePointer = source.c_str();
	glShaderSource(shader, 1, &sourcePointer, nullptr);
	glCompileShader(shader);
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(length, '\0');
		glGetShaderInfoLog(shader, length, nullptr, &infoLog[0]);
		std::cout << infoLog << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}
PixelDome::Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath)
	:_program(0)
{
	std::string vertexSource = LoadFromFile(vertexPath);
	std::string fragmentSource = LoadFromFile(fragmentPath);
	unsigned int vertex = Compile(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragment = Compile(GL_FRAGMENT_SHADER, fragmentSource);
	_program = glCreateProgram();
	glAttachShader(_program, vertex);
	glAttachShader(_program, fragment);
	glLinkProgram(_program);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	int result;
	glGetProgramiv(_program, GL_LINK_STATUS, &result);
	if (!result)
	{
		int length;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);
		std::string infoLog(length, '\0');
		glGetProgramInfoLog(_program, length, nullptr, &infoLog[0]);
		std::cout << infoLog << std::endl;
		glDeleteProgram(_program);
		return;
	}
}
PixelDome::Shader::~Shader()
{
	if (_program != 0)
	{
		glDeleteProgram(_program);
	}
}
PixelDome::Shader::Shader(PixelDome::Shader&& other) noexcept
{
	if (this != &other)
	{
		_program = other._program;
		other._program = 0;
	}
}
PixelDome::Shader& PixelDome::Shader::operator=(PixelDome::Shader&& other) noexcept
{
	if (this != &other)
	{
		if (_program != 0)
		{
			glDeleteProgram(_program);
		}
		_program = other._program;
		other._program = 0;
	}
	return *this;
}
void PixelDome::Shader::Use()
{
	glUseProgram(_program);
}
void PixelDome::Shader::UnUse()
{
	glUseProgram(0);
}
void PixelDome::Shader::SetMat4(std::string_view name, const glm::mat4& value)
{
	int location = glGetUniformLocation(_program, std::string(name).c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
void PixelDome::Shader::SetFloat(std::string_view name, float value)
{
	int location = glGetUniformLocation(_program, std::string(name).c_str());
	glUniform1f(location, value);
}