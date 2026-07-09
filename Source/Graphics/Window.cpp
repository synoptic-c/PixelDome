#include"Window.hpp"
PixelDome::Window::Window(int width, int height, std::string_view title)
{
	_window = glfwCreateWindow(width, height, std::string(title).c_str(), nullptr, nullptr);
	if (!_window)
	{
		std::cout << "Window creation failed" << std::endl;
		return;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	});
}
PixelDome::Window::~Window()
{
	if (_window)
	{
		glfwDestroyWindow(_window);
	}
}
PixelDome::Window& PixelDome::Window::operator=(PixelDome::Window&& other) noexcept
{
	if (this != &other)
	{
		if (_window)
		{
			glfwDestroyWindow(_window);
		}
		_window = other._window;
		other._window = nullptr;
	}
	return *this;
}
GLFWwindow* PixelDome::Window::GetWindow() const
{
	return _window;
}
int PixelDome::Window::WindowShouldClose()
{
	return glfwWindowShouldClose(_window);
}
void PixelDome::Window::SwapBuffers()
{
	glfwSwapBuffers(_window);
}
int PixelDome::Window::GetKey(int key)
{
	return glfwGetKey(_window, key) == GLFW_PRESS;
}
int PixelDome::Window::GetMouseButton(int button)
{
	return glfwGetMouseButton(_window, button) == GLFW_PRESS;
}
int PixelDome::Window::GetWidth()
{
	int width;
	glfwGetFramebufferSize(_window, &width, nullptr);
	return width;
}
int PixelDome::Window::GetHeight()
{
	int height;
	glfwGetFramebufferSize(_window, nullptr, &height);
	return height;
}
double PixelDome::Window::GetMouseX()
{
	double mouseX;
	glfwGetCursorPos(_window, &mouseX, nullptr);
	return mouseX;
}
double PixelDome::Window::GetMouseY()
{
	double mouseY;
	glfwGetCursorPos(_window, nullptr, &mouseY);
	return mouseY;
}
double PixelDome::Window::GetFixMouseX(const PixelDome::Camera& camera)
{
	return camera.GetFixLeft() + GetMouseX() / (GetWidth() / (camera.GetFixRight() - camera.GetFixLeft()));
}
double PixelDome::Window::GetFixMouseY(const PixelDome::Camera& camera)
{
	return camera.GetFixBottom() + (0.0f - GetMouseY() + GetHeight()) / (GetHeight() / (camera.GetFixTop() - camera.GetFixBottom()));
}