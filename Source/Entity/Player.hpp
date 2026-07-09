#pragma once
#include<memory>
#include<vector>
#include<string>
#include<string_view>
#include<nlohmann/json.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"Util/JsonLoader.hpp"
#include"Graphics/Mesh.hpp"
#include"Graphics/Shader.hpp"
#include"Graphics/Texture.hpp"
#include"Graphics/Camera.hpp"
#include"Map/Level.hpp"
#include"Entity/Tile.hpp"
namespace PixelDome
{
	class Player
	{
	private:
		std::unique_ptr<PixelDome::Mesh> _mesh;
		std::unique_ptr<PixelDome::Shader> _shader;
		std::vector<PixelDome::Texture> _textures;
		glm::vec2 _position;
		glm::vec2 _speed;
		glm::vec2 _size;
		float _acceleration;
		float _drag;
		float _width;
		float _height;
		size_t _animationState;
	public:
		Player(const glm::vec2& position);
		bool MoveAndCollide(const PixelDome::Level& level, const PixelDome::Tile& tile, const glm::vec2& speed);
		int CheckLoadLevel(const PixelDome::Level& level);
		void Update(const PixelDome::Level& level, const PixelDome::Tile& tile, bool left, bool right, bool up, bool down, float deltaTime, int& mapIndex);
		void Draw(const PixelDome::Camera& camera);
		const glm::vec2& GetPosition() const;
		void SetPosition(const glm::vec2& position);
		const glm::vec2& GetSpeed() const;
		const glm::vec2& GetSize() const;
		float GetAcceleration() const;
		float GetDrag() const;
		float GetWidth() const;
		float GetHeight() const;
		size_t GetAnimationState() const;
	};
}