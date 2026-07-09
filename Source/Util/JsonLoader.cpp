#include"JsonLoader.hpp"
nlohmann::json PixelDome::JsonLoader::_cache = nlohmann::json::object();
PixelDome::JsonLoader::JsonLoader(std::string_view path)
{
	_cache = LoadJson(path);
}
const nlohmann::json& PixelDome::JsonLoader::GetJson()
{
	return _cache;
}