#pragma once
#include<cmath>
#include<imgui/imgui.h>
#include"Entity/Player.hpp"
namespace PixelDome
{
	class DebugGui
	{
	private:
		bool _pressedF1;
	public:
		void Render(const PixelDome::Player& player);
	};
}