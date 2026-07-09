#include"Camera.hpp"
PixelDome::Camera::Camera()
{
	PixelDome::JsonLoader jsonLoader;
	nlohmann::json jsonProjection = PixelDome::LoadJson(jsonLoader.GetJson()["projection"].get<std::string>());
	_left = jsonProjection["left"].get<float>();
	_right = jsonProjection["right"].get<float>();
	_bottom = jsonProjection["bottom"].get<float>();
	_top = jsonProjection["top"].get<float>();
	_zNear = jsonProjection["zNear"].get<float>();
	_zFar = jsonProjection["zFar"].get<float>();
	_fixLeft = _left;
	_fixRight = _right;
	_fixTop = _top;
	_fixBottom = _bottom;
}
float PixelDome::Camera::GetLeft() const
{
	return _left;
}
float PixelDome::Camera::GetRight() const
{
	return _right;
}
float PixelDome::Camera::GetTop() const
{
	return _top;
}
float PixelDome::Camera::GetBottom() const
{
	return _bottom;
}
float PixelDome::Camera::GetFixLeft() const
{
	return _fixLeft;
}
float PixelDome::Camera::GetFixRight() const
{
	return _fixRight;
}
float PixelDome::Camera::GetFixTop() const
{
	return _fixTop;
}
float PixelDome::Camera::GetFixBottom() const
{
	return _fixBottom;
}
void PixelDome::Camera::SetProjection(int widthWindow, int heightWindow)
{
	float projectionWidth = _right - _left;
	float projectionHeight = _top - _bottom;
	float proportionProjection = projectionWidth / projectionHeight;
	float proportionWindow = (float)widthWindow / heightWindow;
	_fixLeft = _left;
	_fixRight = _right;
	_fixBottom = _bottom;
	_fixTop = _top;
	if (proportionWindow < proportionProjection)
	{
		_fixLeft += (projectionWidth - projectionHeight * proportionWindow) / 2.0f;
		_fixRight -= (projectionWidth - projectionHeight * proportionWindow) / 2.0f;
	}
	else if (proportionWindow > proportionProjection)
	{
		_fixBottom += (projectionHeight - projectionWidth / proportionWindow) / 2.0f;
		_fixTop -= (projectionHeight - projectionWidth / proportionWindow) / 2.0f;
	}
	_projection = glm::ortho(_fixLeft, _fixRight, _fixBottom, _fixTop, _zNear, _zFar);
}
glm::mat4 PixelDome::Camera::GetProjection() const
{
	return _projection;
}
glm::vec2 PixelDome::Camera::GetView() const
{
	return _view;
}
void PixelDome::Camera::SetView(const glm::vec2& view)
{
	_view = view;
}
void PixelDome::Camera::MoveView(const glm::vec2& view)
{
	_view += view;
}