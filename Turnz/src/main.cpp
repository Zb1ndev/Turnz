#include <iostream>
#include <string>
#include <SDL.h>
#include "math/math.h"

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	auto gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	auto gScreenSurface = SDL_GetWindowSurface(gWindow);
	auto gHelloWorld = SDL_LoadBMP("C:/dev/Turnz/Turnz/src/Blob.bmp");
	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);

	SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }

	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();

	return 0;

}



