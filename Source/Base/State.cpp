#include"State.hpp"
PixelDome::State::State(int width, int height, std::string_view title)
	:_window(width, height, title), _imGuiManager(_window.GetWindow())
{
}
void PixelDome::State::Run()
{
	_game = std::make_unique<PixelDome::Game>();
	float lastTime = glfwGetTime();
	while (!_window.WindowShouldClose())
	{
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		_imGuiManager.NewFrame();
		_game->Update(_window, deltaTime);
		_game->Draw();
		_imGuiManager.Render();
		_window.SwapBuffers();
	}
}