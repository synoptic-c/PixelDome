#include"Level.hpp"
PixelDome::Level::Level(std::string_view path)
{
	loadLevel(path);
}
void PixelDome::Level::loadLevel(std::string_view path)
{
	nlohmann::json jsonLevel = PixelDome::LoadJson(path);
	_widthCount = jsonLevel["widthCount"].get<size_t>();
	_heightCount = jsonLevel["heightCount"].get<size_t>();
	_mapIndices = jsonLevel["mapIndices"].get<std::vector<int>>();
	_loadPositionXs = jsonLevel["loadPositionXs"].get<std::vector<float>>();
	_loadPositionYs = jsonLevel["loadPositionYs"].get<std::vector<float>>();
	_mapPaths = jsonLevel["mapPaths"].get<std::vector<std::string>>();
	_data = jsonLevel["levelData"].get<std::vector<size_t>>();
}
size_t PixelDome::Level::GetWidthCount() const
{
	return _widthCount;
}
size_t PixelDome::Level::GetHeightCount() const
{
	return _heightCount;
}
std::optional<size_t> PixelDome::Level::GetTile(size_t x, size_t y) const
{
	if (x >= 0 && y >= 0 && x < _widthCount && y < _heightCount)
	{
		return _data[x + y * _widthCount];
	}
	return std::nullopt;
}
const std::vector<size_t>& PixelDome::Level::GetData() const
{
	return _data;
}
const std::vector<int>& PixelDome::Level::GetMapIndices() const
{
	return _mapIndices;
}
void PixelDome::Level::SetMapPath(int index, std::string_view value)
{
	if (index > -1 && index < _mapPaths.size())
	{
		_mapPaths[index] = value;
	}
}
void PixelDome::Level::SetLoadPositionX(int index, float value)
{
	if (index > -1 && index < _loadPositionXs.size())
	{
		_loadPositionXs[index] = value;
	}
}
void PixelDome::Level::SetLoadPositionY(int index, float value)
{
	if (index > -1 && index < _loadPositionYs.size())
	{
		_loadPositionYs[index] = value;
	}
}
std::string PixelDome::Level::GetMapPath(int index) const
{
	if (index > -1 && index < _mapPaths.size())
	{
		return _mapPaths[index];
	}
	return "";
}
float PixelDome::Level::GetLoadPositionX(int index) const
{
	if (index > -1 && index < _loadPositionXs.size())
	{
		return _loadPositionXs[index];
	}
	return 0.0f;
}
float PixelDome::Level::GetLoadPositionY(int index) const
{
	if (index > -1 && _loadPositionYs.size())
	{
		return _loadPositionYs[index];
	}
	return 0.0f;
}
const std::vector<std::string>& PixelDome::Level::GetMapPaths() const
{
	return _mapPaths;
}
const std::vector<float>& PixelDome::Level::GetLoadPositionXs() const
{
	return _loadPositionXs;
}
const std::vector<float>& PixelDome::Level::GetLoadPositionYs() const
{
	return _loadPositionYs;
}
void PixelDome::Level::AddLoadMapPath(std::string_view value)
{
	_mapPaths.emplace_back(value);
}
void PixelDome::Level::AddLoadPositionX(float value)
{
	_loadPositionXs.emplace_back(value);
}
void PixelDome::Level::AddLaodPositionY(float value)
{
	_loadPositionYs.emplace_back(value);
}
void PixelDome::Level::RemoveLoadMapPath(int index)
{
	if (index > -1 && index < _mapPaths.size())
	{
		_mapPaths.erase(_mapPaths.begin() + index);
	}
}
void PixelDome::Level::RemoveLoadPositionX(int index)
{
	if (index > -1 && index < _loadPositionXs.size())
	{
		_loadPositionXs.erase(_loadPositionXs.begin() + index);
	}
}
void PixelDome::Level::RemoveLoadPositionY(int index)
{
	if (index > -1 && index < _loadPositionYs.size())
	{
		_loadPositionYs.erase(_loadPositionYs.begin() + index);
	}
}
int PixelDome::Level::GetMapIndex(size_t x, size_t y) const
{
	if (x >= 0 && y >= 0 && x < _widthCount && y < _heightCount)
	{
		return _mapIndices[x + y * _widthCount];
	}
	return -1;
}
void PixelDome::Level::SetMapIndex(size_t x, size_t y, int value)
{
	if (x >= 0 && y >= 0 && x < _widthCount && y < _heightCount)
	{
		_mapIndices[x + y * _widthCount] = value;
	}
}
void PixelDome::Level::SetLevel(size_t widthCount, size_t heightCount)
{
	_widthCount = widthCount;
	_heightCount = heightCount;
	_data.assign(_widthCount * _heightCount, 0);
}
void PixelDome::Level::SetMapIndices(size_t widthCount, size_t heightCount)
{
	_widthCount = widthCount;
	_heightCount = heightCount;
	_mapIndices.assign(_widthCount * _heightCount, -1);
}
void PixelDome::Level::SetTile(size_t x, size_t y, size_t value)
{
	if (x >= 0 && y >= 0 && x < _widthCount && y < _heightCount)
	{
		_data[x + y * _widthCount] = value;
	}
}