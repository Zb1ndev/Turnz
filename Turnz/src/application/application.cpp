#include <SDL.h>
#include <iostream>
#include "application.h"

const char* Application::Init(const char* title, int w, int h) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return "Failed to Initialize SLD2";
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE);
	if (window == NULL) return "Failed to Create Window";
	screenSurface = SDL_GetWindowSurface(window);

}
void Application::Close() {

	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();

}

Application::Application(const char* title, int w, int h) {
	Init(title, w, h);
}
Application::~Application(){}

