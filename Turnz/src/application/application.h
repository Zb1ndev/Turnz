#pragma once
#include <SDL2/SDL.h>

class Application {

public:

	SDL_Window* window;
	SDL_GLContext glContext = nullptr;

	const char* Init(const char* title, int w, int h);
	void Close();

	Application(const char* title, int w, int h);
	~Application();

};