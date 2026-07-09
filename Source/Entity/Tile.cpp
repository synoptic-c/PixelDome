#include"Tile.hpp"
PixelDome::Tile::Tile()
{
	PixelDome::JsonLoader jsonLoader;
	nlohmann::json jsonQuad = PixelDome::LoadJson(jsonLoader.GetJson()["quad"].get<std::string>());
	_mesh = std::make_unique<PixelDome::Mesh>(
		jsonQuad["vertices"].get<std::vector<float>>(),
		jsonQuad["indices"].get<std::vector<unsigned int>>(),
		jsonQuad["layouts"].get<std::vector<int>>()
	);
	nlohmann::json jsonTile = PixelDome::LoadJson(jsonLoader.GetJson()["tile"].get<std::string>());
	std::vector<std::string> vertexPaths = jsonTile["vertexPaths"].get<std::vector<std::string>>();
	std::vector<std::string> fragmentPaths = jsonTile["fragmentPaths"].get<std::vector<std::string>>();
	_shaders.reserve(vertexPaths.size());
	for (size_t i = 0;i < vertexPaths.size();i++)
	{
		_shaders.emplace_back(
			vertexPaths[i],
			fragmentPaths[i]
		);
	}
	std::vector<std::string> texturesPath = jsonTile["texturePaths"].get<std::vector<std::string>>();
	_textures.reserve(texturesPath.size());
	for (const std::string& texturePath : texturesPath)
	{
		_textures.emplace_back(texturePath);
	}
	_widthCount = jsonTile["widthCount"].get<size_t>();
	_heightCount = jsonTile["heightCount"].get<size_t>();
	_halfSize = jsonTile["halfSize"].get<float>();
	_names = jsonTile["names"].get<std::vector<std::string>>();
	_shaderIndices = jsonTile["shaderIndices"].get<std::vector<size_t>>();
	_solids = jsonTile["solids"].get<std::vector<unsigned char>>();
	_positions.reserve(_widthCount * _heightCount);
	_indices.reserve(_widthCount * _heightCount);
	for (size_t x = 0; x < _widthCount; x++)
	{
		for (size_t y = 0; y < _heightCount; y++)
		{
			_positions.emplace_back(glm::vec2(x + _halfSize, y + _halfSize));
			_indices.emplace_back(glm::uvec2(x, y));
		}
	}
}
void PixelDome::Tile::Update(const PixelDome::Camera& camera)
{
	glm::vec2 offsetCamera = camera.GetView() - _halfSize;
	for (size_t i = 0;i < _positions.size();i++)
	{
		if (_positions[i].x - offsetCamera.x < 0)
		{
			_positions[i].x += _widthCount;
			_indices[i].x += _widthCount;
		}
		if (_positions[i].x - offsetCamera.x > _widthCount)
		{
			_positions[i].x -= _widthCount;
			_indices[i].x -= _widthCount;
		}
		if (_positions[i].y - offsetCamera.y < 0)
		{
			_positions[i].y += _heightCount;
			_indices[i].y += _heightCount;
		}
		if (_positions[i].y - offsetCamera.y > _heightCount)
		{
			_positions[i].y -= _heightCount;
			_indices[i].y -= _heightCount;
		}
	}
}
void PixelDome::Tile::Draw(const PixelDome::Camera& camera, const PixelDome::Level& level, float time)
{
	for (size_t i = 0; i < _positions.size(); i++)
	{
		if (_indices[i].x < level.GetWidthCount() && _indices[i].y < level.GetHeightCount())
		{
			size_t shaderIndex = _shaderIndices[level.GetTile(_indices[i].x, _indices[i].y).value()];
			_shaders[shaderIndex].Use();
			if (_names[level.GetTile(_indices[i].x, _indices[i].y).value()] == "water")
			{
				_shaders[shaderIndex].SetFloat("u_time", time);
			}
			_shaders[shaderIndex].SetMat4("u_projection", camera.GetProjection());
			_shaders[shaderIndex].SetMat4("u_view", glm::translate(glm::mat4(1.0f), glm::vec3(-camera.GetView(), 0.0f)));
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(_positions[i], 0.0f));
			_shaders[shaderIndex].SetMat4("u_model", model);
			_textures[level.GetTile(_indices[i].x, _indices[i].y).value()].Bind();
			_mesh->Draw();
		}
	}
}
const std::vector<std::string>& PixelDome::Tile::GetNames() const
{
	return _names;
}
const std::vector<PixelDome::Texture>& PixelDome::Tile::GetTextures() const
{
	return _textures;
}
unsigned char PixelDome::Tile::GetSolid(std::optional<size_t> i) const
{
	if (i.has_value())
	{
		return _solids[i.value()];
	}
	return 0;
}
const std::vector<unsigned char>& PixelDome::Tile::GetSolids() const
{
	return _solids;
}