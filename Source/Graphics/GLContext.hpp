#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
namespace PixelDome
{
	class GLContext
	{
	public:
		static void GlfwInitialize(int major, int minor);
		static void GladInitialize();
		static void Destroy();
	};
}