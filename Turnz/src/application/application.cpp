#include <SDL.h>
#include <iostream>

#include "application.h"
#include "../math/math.h"

// Write Main Code Here
void Application::Run() {

	auto helloWorld = SDL_LoadBMP("C:/dev/Turnz/Turnz/src/Blob.bmp");
	SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);

	SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }

	SDL_FreeSurface(helloWorld);
	helloWorld = NULL;
	Close();

}

const char* Application::Init(const char* title, int w, int h) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return "Failed to Initialize SLD2";
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
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

