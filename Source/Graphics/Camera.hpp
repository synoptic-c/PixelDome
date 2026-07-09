#pragma once
#include<nlohmann/json.hpp>
#include<Util/JsonLoader.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
namespace PixelDome
{
	class Camera
	{
	private:
		float _left;
		float _right;
		float _bottom;
		float _top;
		float _zNear;
		float _zFar;
		float _fixLeft;
		float _fixRight;
		float _fixBottom;
		float _fixTop;
		glm::vec2 _view;
		glm::mat4 _projection;
	public:
		Camera();
		float GetLeft() const;
		float GetRight() const;
		float GetTop() const;
		float GetBottom() const;
		float GetFixLeft() const;
		float GetFixRight() const;
		float GetFixTop() const;
		float GetFixBottom() const;
		void SetProjection(int widthWindow, int heightWindow);
		glm::mat4 GetProjection() const;
		glm::vec2 GetView() const;
		void SetView(const glm::vec2& view);
		void MoveView(const glm::vec2& view);
	};
}