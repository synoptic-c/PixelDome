#pragma once
#include<memory>
#include<vector>
#include<string>
#include<string_view>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include"Util/JsonLoader.hpp"
#include"Graphics/Window.hpp"
#include"Graphics/Camera.hpp"
#include"Map/Level.hpp"
#include"Entity/Player.hpp"
#include"Entity/Tile.hpp"
#include"Debug/DebugGui.hpp"
#include"Debug/Editor.hpp"
namespace PixelDome
{
	class Game
	{
	private:
		PixelDome::DebugGui _debugGui;
		PixelDome::Camera _camera;
		std::unique_ptr<PixelDome::Editor> _editor;
		std::unique_ptr<PixelDome::Player> _player;
		std::unique_ptr<PixelDome::Level> _level;
		std::unique_ptr<PixelDome::Tile> _tile;
	public:
		Game();
		void Update(PixelDome::Window& window, float deltaTime);
		void Draw();
	};
}