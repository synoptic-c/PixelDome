#pragma once
#include<memory>
#include<vector>
#include<string>
#include<string_view>
#include<cstddef>
#include<nlohmann/json.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include"Util/JsonLoader.hpp"
#include"Graphics/GLContext.hpp"
#include"Graphics/Window.hpp"
#include"Gui/ImGuiManager.hpp"
#include"Game.hpp"
namespace PixelDome
{
	class State
	{
	private:
		PixelDome::Window _window;
		PixelDome::ImGuiManager _imGuiManager;
		std::unique_ptr<PixelDome::Game> _game;
	public:
		State(int width, int height, std::string_view title);
		void Run();
	};
}