#pragma once
#include<iostream>
#include<string>
#include<string_view>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"Graphics/Camera.hpp"
namespace PixelDome
{
	class Window
	{
	private:
		GLFWwindow* _window = nullptr;
	public:
		Window() = default;
		Window(int width, int height, std::string_view title);
		~Window();
		PixelDome::Window& operator=(PixelDome::Window&& other) noexcept;
		GLFWwindow* GetWindow() const;
		int WindowShouldClose();
		void SwapBuffers();
		int GetKey(int key);
		int GetMouseButton(int button);
		int GetWidth();
		int GetHeight();
		double GetMouseX();
		double GetMouseY();
		double GetFixMouseX(const PixelDome::Camera& camera);
		double GetFixMouseY(const PixelDome::Camera& camera);
	};
}