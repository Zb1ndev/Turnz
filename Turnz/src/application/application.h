#pragma once

#include <SDL.h>
#include <iostream>

#include "application.h"
#include "../math/math.h"

class Application {

public:

	SDL_Window* window;
	SDL_Surface* screenSurface;

	const char* Init(const char* title, int w, int h);
	void Run();
	void Close();

	Application(const char* title, int w, int h);
	~Application();

};