#pragma once
#include<iostream>
#include<string>
#include<string_view>
#include<fstream>
#include<nlohmann/json.hpp>
namespace PixelDome
{
	inline nlohmann::json LoadJson(std::string_view path)
	{
		std::fstream file(std::string(path), std::ios::in);
		if (!file.is_open())
		{
			std::cout << "Failed to open file" << " " << path << std::endl;
			return nlohmann::json();
		}
		nlohmann::json json;
		file >> json;
		return json;
	}
	class JsonLoader
	{
	private:
		static nlohmann::json _cache;
	public:
		JsonLoader() = default;
		JsonLoader(std::string_view path);
		static const nlohmann::json& GetJson();
	};
}