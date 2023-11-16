#pragma once
#include <SDL2/SDL.h>

class Application {

public:

	SDL_Window* window;
	SDL_GLContext glContext = nullptr;

	Application(const char* title, int w, int h, void (*startPointer)(), void (*updatePointer)(), void (*onClosePointer)());
	~Application();

private:
	const char* Init(const char* title, int w, int h);
	void Close();

	

};