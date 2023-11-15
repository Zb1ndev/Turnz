#pragma once
#include <SDL.h>

class Application {

public:

	SDL_Window* window;
	SDL_Surface* screenSurface;

	const char* Init(const char* title, int w, int h);
	void Close();

	Application(const char* title, int w, int h);
	~Application();

};