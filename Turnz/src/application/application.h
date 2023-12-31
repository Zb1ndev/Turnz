#pragma once
#include <SDL2/SDL.h>
#include <GLAD/glad.h>

#include <string>

#include "../renderer/renderer.h"
#include "../input/input.h"

class Application {

public:

	static Application* instance;
	static Renderer::Scene* currentScene;

	SDL_Window* window;
	SDL_GLContext glContext = nullptr;
	Renderer renderer;

	int width, height;

	Application() = default;
	Application(
		const char* title,
		int w, int h,
		std::string vertexShaderDirectory,
		std::string fragmentShaderDirectory,
		Renderer::Scene scene,
		void (*startPointer)() = NULL,
		void (*updatePointer)() = NULL,
		void (*onClosePointer)() = NULL
	);
	~Application();

private:

	const char* Init(const char* title, int w, int h);
	void UpdateWindowProperties();
	void Close();

};