#pragma once
#include<string>
#include<string_view>
#include<fstream>
#include<optional>
#include<string.h>
#include<nlohmann/json.hpp>
#include<imgui/imgui.h>
#include"Util/JsonLoader.hpp"
#include"Graphics/Window.hpp"
#include"Graphics/Texture.hpp"
#include"Graphics/Camera.hpp"
#include"Map/Level.hpp"
#include"Entity/Tile.hpp"
#include"Entity/Player.hpp"
namespace PixelDome
{
	class Editor
	{
	private:
		bool _pressedF2;
		size_t _chooseTile;
		size_t _tempWidthCount;
		size_t _tempHeightCount;
		float _tempPlayerPositionX;
		float _tempPlayerPositionY;
		size_t _tempMouseX;
		size_t _tempMouseY;
		std::optional<size_t> _tempChooseIndex;
		std::string _tempMapName;
		int _tempSelected;
		char _tempSetMapPath[128];
		float _tempSetLoadPositionX;
		float _tempSetLoadPositionY;
		int _tempChooseItem;
	public:
		Editor(std::string_view path);
		void UpdateTemp(std::string_view path);
		void Render(bool mouseLeft, bool mouseRight, const PixelDome::Player& player, PixelDome::Window& window, const PixelDome::Camera& camera, PixelDome::Level& level, const PixelDome::Tile& tile);
	};
}