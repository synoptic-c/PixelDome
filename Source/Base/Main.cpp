#include"State.hpp"
int main()
{
	PixelDome::JsonLoader jsonLoader("Assets/Config/Path.json");
	PixelDome::GLContext::GlfwInitialize(3, 3);
	nlohmann::json windowConfig = PixelDome::LoadJson(PixelDome::JsonLoader::GetJson()["window"].get<std::string>());
	PixelDome::State state(windowConfig["width"].get<int>(), windowConfig["height"].get<int>(), windowConfig["title"].get<std::string>());
	PixelDome::GLContext::GladInitialize();
	state.Run();
	PixelDome::GLContext::Destroy();
}