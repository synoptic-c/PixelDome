#pragma once
#include<string>
#include<string_view>
#include<vector>
#include<cstddef>
#include<optional>
#include<nlohmann/json.hpp>
#include"Util/JsonLoader.hpp"
namespace PixelDome
{
	class Level
	{
	private:
		std::vector<size_t> _data;
		std::vector<int> _mapIndices;
		std::vector<float> _loadPositionXs;
		std::vector<float> _loadPositionYs;
		std::vector<std::string> _mapPaths;
		size_t _widthCount;
		size_t _heightCount;
	public:
		Level(std::string_view path);
		void loadLevel(std::string_view path);
		size_t GetWidthCount() const;
		size_t GetHeightCount() const;
		std::optional<size_t> GetTile(size_t x, size_t y) const;
		const std::vector<size_t>& GetData() const;
		const std::vector<int>& GetMapIndices() const;
		void SetMapPath(int index, std::string_view value);
		void SetLoadPositionX(int index, float value);
		void SetLoadPositionY(int index, float value);
		std::string GetMapPath(int index) const;
		float GetLoadPositionX(int index) const;
		float GetLoadPositionY(int index) const;
		const std::vector<std::string>& GetMapPaths() const;
		const std::vector<float>& GetLoadPositionXs() const;
		const std::vector<float>& GetLoadPositionYs() const;
		void AddLoadMapPath(std::string_view value);
		void AddLoadPositionX(float value);
		void AddLaodPositionY(float value);
		void RemoveLoadMapPath(int index);
		void RemoveLoadPositionX(int index);
		void RemoveLoadPositionY(int index);
		int GetMapIndex(size_t x, size_t y) const;
		void SetMapIndex(size_t x, size_t y, int value);
		void SetLevel(size_t widthCount, size_t heightCount);
		void SetMapIndices(size_t widthCount, size_t heightCount);
		void SetTile(size_t x, size_t y, size_t value);
	};
}