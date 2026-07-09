#include"GLContext.hpp"
void PixelDome::GLContext::GlfwInitialize(int major, int minor)
{
	if (!glfwInit())
	{
		std::cout << "Glfw initialization failed" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_TRUE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
}
void PixelDome::GLContext::GladInitialize()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Glad initialization failed" << std::endl;
		glfwTerminate();
		return;
	}
}
void PixelDome::GLContext::Destroy()
{
	glfwTerminate();
}