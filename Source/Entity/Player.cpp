#include"Player.hpp"
PixelDome::Player::Player(const glm::vec2& position)
{
	PixelDome::JsonLoader jsonLoader;
	nlohmann::json jsonQuad = PixelDome::LoadJson(jsonLoader.GetJson()["quad"].get<std::string>());
	_mesh = std::make_unique<PixelDome::Mesh>(
		jsonQuad["vertices"].get<std::vector<float>>(),
		jsonQuad["indices"].get<std::vector<unsigned int>>(),
		jsonQuad["layouts"].get<std::vector<int>>()
	);
	nlohmann::json jsonPlayer = PixelDome::LoadJson(jsonLoader.GetJson()["player"].get<std::string>());
	_shader = std::make_unique<PixelDome::Shader>(
		jsonPlayer["vertexPath"].get<std::string>(),
		jsonPlayer["fragmentPath"].get<std::string>()
	);
	std::vector<std::string> texturesPath = jsonPlayer["texturePaths"].get<std::vector<std::string>>();
	_textures.reserve(texturesPath.size());
	for (const std::string& texturePath : texturesPath)
	{
		_textures.emplace_back(texturePath);
	}
	_position = position;
	_speed = glm::vec2(jsonPlayer["speed"]["x"].get<float>(), jsonPlayer["speed"]["y"].get<float>());
	_size = glm::vec2(jsonPlayer["size"]["x"].get<float>(), jsonPlayer["size"]["y"].get<float>());
	_acceleration = jsonPlayer["acceleration"].get<float>();
	_drag = jsonPlayer["drag"].get<float>();
	_width = jsonPlayer["width"].get<float>();
	_height = jsonPlayer["height"].get<float>();
	_animationState = jsonPlayer["animationState"].get<size_t>();
}
bool PixelDome::Player::MoveAndCollide(const PixelDome::Level& level, const PixelDome::Tile& tile, const glm::vec2& speed)
{
	float leftPlayer = _position.x - _width;
	float rightPlayer = _position.x + _width;
	float upPlayer = _position.y + _height;
	float downPlayer = _position.y - _height;
	if (rightPlayer > 0 && upPlayer > 0 && leftPlayer < level.GetWidthCount() && downPlayer < level.GetHeightCount())
	{
 		if ((tile.GetSolid(level.GetTile(leftPlayer, upPlayer)) > 0 || tile.GetSolid(level.GetTile(leftPlayer, _position.y)) > 0 || tile.GetSolid(level.GetTile(leftPlayer, downPlayer)) > 0) && speed.x < 0.0f)
		{
			_position.x += 1.0f - std::fmod(leftPlayer, 1.0f);
			return true;
		}
		else if ((tile.GetSolid(level.GetTile(rightPlayer, upPlayer)) > 0 || tile.GetSolid(level.GetTile(rightPlayer, _position.y)) > 0 || tile.GetSolid(level.GetTile(rightPlayer, downPlayer)) > 0) && speed.x > 0.0f)
		{
			_position.x -= std::fmod(rightPlayer, 1.0f) + 0.0001f;
			return true;
		}
		if ((tile.GetSolid(level.GetTile(leftPlayer, upPlayer)) > 0 || tile.GetSolid(level.GetTile(_position.x, upPlayer)) > 0 || tile.GetSolid(level.GetTile(rightPlayer, upPlayer)) > 0) && speed.y > 0.0f)
		{
			_position.y -= std::fmod(upPlayer, 1.0f) + 0.0001f;
			return true;
		}
		else if ((tile.GetSolid(level.GetTile(leftPlayer, downPlayer)) > 0 || tile.GetSolid(level.GetTile(_position.x, downPlayer)) > 0 || tile.GetSolid(level.GetTile(rightPlayer, downPlayer)) > 0) && speed.y < 0.0f)
		{
			_position.y += 1.0f - std::fmod(downPlayer, 1.0f);
			return true;
		}
		return false;
	}
}
int PixelDome::Player::CheckLoadLevel(const PixelDome::Level& level)
{
	float leftPlayer = _position.x - _width;
	float rightPlayer = _position.x + _width;
	float upPlayer = _position.y + _height;
	float downPlayer = _position.y - _height;
	if (rightPlayer > 0 && upPlayer > 0 && leftPlayer < level.GetWidthCount() && downPlayer < level.GetHeightCount())
	{
		if (level.GetMapIndex(leftPlayer, upPlayer) > -1)
		{
			return level.GetMapIndex(leftPlayer, upPlayer);
		}
		if (level.GetMapIndex(leftPlayer, _position.y) > -1)
		{
			return level.GetMapIndex(leftPlayer, _position.y);
		}
		if (level.GetMapIndex(leftPlayer, downPlayer) > -1)
		{
			return level.GetMapIndex(leftPlayer, downPlayer);
		}
		if (level.GetMapIndex(rightPlayer, upPlayer) > -1)
		{
			return level.GetMapIndex(rightPlayer, upPlayer);
		}
		if (level.GetMapIndex(rightPlayer, _position.y) > -1)
		{
			return level.GetMapIndex(rightPlayer, _position.y);
		}
		if (level.GetMapIndex(rightPlayer, downPlayer) > -1)
		{
			return level.GetMapIndex(rightPlayer, downPlayer);
		}
		if (level.GetMapIndex(leftPlayer, upPlayer) > -1)
		{
			return level.GetMapIndex(leftPlayer, upPlayer);
		}
		if (level.GetMapIndex(_position.x, upPlayer) > -1)
		{
			return level.GetMapIndex(_position.x, upPlayer);
		}
		if (level.GetMapIndex(rightPlayer, upPlayer) > -1)
		{
			return level.GetMapIndex(rightPlayer, upPlayer);
		}
		if (level.GetMapIndex(leftPlayer, downPlayer) > -1)
		{
			return level.GetMapIndex(leftPlayer, downPlayer);
		}
		if (level.GetMapIndex(_position.x, downPlayer) > -1)
		{
			return level.GetMapIndex(_position.x, downPlayer);
		}
		if (level.GetMapIndex(rightPlayer, downPlayer) > -1)
		{
			return level.GetMapIndex(rightPlayer, downPlayer);
		}
	}
	return -1;
}
void PixelDome::Player::Update(const PixelDome::Level& level, const PixelDome::Tile& tile, bool left, bool right, bool up, bool down, float deltaTime, int& mapIndex)
{
	_speed += glm::vec2(right - left, up - down) * _acceleration;
	_speed *= _drag;
	_position.y += _speed.y * deltaTime;
	if (std::abs(_speed.y) < 0.0001f)
	{
		_speed.y = 0.0f;
	}
	if (MoveAndCollide(level, tile, glm::vec2(0.0f, _speed.y)) == true)
	{
		_speed.y = 0.0f;
	}
	_position.x += _speed.x * deltaTime;
	if (std::abs(_speed.x) < 0.0001f)
	{
		_speed.x = 0.0f;
	}
	if (MoveAndCollide(level, tile, glm::vec2(_speed.x, 0.0f)) == true)
	{
		_speed.x = 0.0f;
	}
	mapIndex = CheckLoadLevel(level);
}
void PixelDome::Player::Draw(const PixelDome::Camera& camera)
{
	_shader->Use();
	_shader->SetMat4("u_projection", camera.GetProjection());
	_shader->SetMat4("u_view", glm::translate(glm::mat4(1.0f), glm::vec3(-camera.GetView(), 0.0f)));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(_position.x, _position.y, 0.0f));
	model = glm::scale(model, glm::vec3(_size, 0.0f));
	_shader->SetMat4("u_model", model);
	_textures[_animationState].Bind();
	_mesh->Draw();
}
const glm::vec2& PixelDome::Player::GetPosition() const
{
	return _position;
}
void PixelDome::Player::SetPosition(const glm::vec2& position)
{
	_position = position;
}
const glm::vec2& PixelDome::Player::GetSpeed() const
{
	return _speed;
}
const glm::vec2& PixelDome::Player::GetSize() const
{
	return _size;
}
float PixelDome::Player::GetAcceleration() const
{
	return _acceleration;
}
float PixelDome::Player::GetDrag() const
{
	return _drag;
}
float PixelDome::Player::GetWidth() const
{
	return _width;
}
float PixelDome::Player::GetHeight() const
{
	return _height;
}
size_t PixelDome::Player::GetAnimationState() const
{
	return _animationState;
}