#include"Game.hpp"
PixelDome::Game::Game()
{
	PixelDome::JsonLoader jsonLoader;
	nlohmann::json jsonQuad = PixelDome::LoadJson(jsonLoader.GetJson()["quad"].get<std::string>());
	std::string levelPath = "Assets/Levels/Scene.json";
	nlohmann::json jsonLevel = PixelDome::LoadJson(levelPath);
	_player = std::make_unique<PixelDome::Player>(
		glm::vec2(jsonLevel["playerPosition"]["x"].get<float>(), jsonLevel["playerPosition"]["y"].get<float>())
	);
	_tile = std::make_unique<PixelDome::Tile>();
	_level = std::make_unique<PixelDome::Level>(levelPath);
	_editor = std::make_unique<PixelDome::Editor>(levelPath);
}
void PixelDome::Game::Update(PixelDome::Window& window, float deltaTime)
{
	_camera.SetProjection(window.GetWidth(), window.GetHeight());
	int mapIndex;
	_player->Update(*_level, *_tile, window.GetKey(GLFW_KEY_A), window.GetKey(GLFW_KEY_D), window.GetKey(GLFW_KEY_W), window.GetKey(GLFW_KEY_S), deltaTime, mapIndex);
	if (mapIndex > -1)
	{
		PixelDome::JsonLoader jsonLoader;
		std::string mapPath = jsonLoader.GetJson()["mapSaveDefault"].get<std::string>() + _level->GetMapPath(mapIndex) + ".json";
		_player->SetPosition(glm::vec2(_level->GetLoadPositionX(mapIndex), _level->GetLoadPositionY(mapIndex)));
		_level->loadLevel(mapPath);
		_editor->UpdateTemp(mapPath);
	}
	_camera.SetView(glm::vec2(_player->GetPosition().x - _camera.GetRight() / 2.0f, _player->GetPosition().y - _camera.GetTop() / 2.0f));
	_tile->Update(_camera);
	_editor->Render(window.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT), window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT), *_player, window, _camera, *_level, *_tile);
	_debugGui.Render(*_player);
}
void PixelDome::Game::Draw()
{
	_tile->Draw(_camera, *_level, glfwGetTime());
	_player->Draw(_camera);
}