#pragma once
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
namespace PixelDome
{
	class ImGuiManager
	{
	public:
		ImGuiManager(GLFWwindow* window);
		~ImGuiManager();
		void NewFrame();
		void Render();
	};
}