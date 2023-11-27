#pragma once
#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include "../renderer/renderer.h"

class Application {

public:

	SDL_Window* window;
	SDL_GLContext glContext = nullptr;
	Renderer renderer;

	Application(const char *title, int w, int h, void (*startPointer)(), void (*updatePointer)(), void (*onClosePointer)());
	~Application();

private:

	const char* Init(const char* title, int w, int h);
	void Close();

};