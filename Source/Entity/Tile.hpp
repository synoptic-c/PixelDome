#pragma once
#include<memory>
#include<vector>
#include<string>
#include<string_view>
#include<cstddef>
#include<optional>
#include<cmath>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Util/JsonLoader.hpp"
#include"Graphics/Camera.hpp"
#include"Graphics/Mesh.hpp"
#include"Graphics/Shader.hpp"
#include"Graphics/Texture.hpp"
#include"Map/Level.hpp"
namespace PixelDome
{
	class Tile
	{
	private:
		std::unique_ptr<PixelDome::Mesh> _mesh;
		std::vector<PixelDome::Shader> _shaders;
		std::vector<PixelDome::Texture> _textures;
		std::vector<glm::vec2> _positions;
		std::vector<glm::uvec2> _indices;
		std::vector<std::string> _names;
		std::vector<size_t> _shaderIndices;
		std::vector<unsigned char> _solids;
		size_t _widthCount;
		size_t _heightCount;
		float _halfSize;
	public:
		Tile();
		void Update(const PixelDome::Camera& camera);
		void Draw(const PixelDome::Camera& camera, const PixelDome::Level& level, float time);
		const std::vector<std::string>& GetNames() const;
		const std::vector<PixelDome::Texture>& GetTextures() const;
		unsigned char GetSolid(std::optional<size_t> i) const;
		const std::vector<unsigned char>& GetSolids() const;
	};
}