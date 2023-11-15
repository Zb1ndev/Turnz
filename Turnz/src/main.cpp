#include <SDL.h>
#include <iostream>

#include "math/math.h"
#include "input/input.h"
#include "application/application.h"

int main(int argc, char** argv) {

	Application app = Application("Turnz", 640, 480);

	auto helloWorld = SDL_LoadBMP("C:/dev/Turnz/Turnz/src/Blob.bmp");
	SDL_BlitSurface(helloWorld, NULL, app.screenSurface, NULL);
	SDL_UpdateWindowSurface(app.window);

	SDL_Event e; 
	bool quit = false; 
	while (quit == false) { 
		while (SDL_PollEvent(&e)) { 
			switch (e.type) {
			case SDL_QUIT:
				quit = true;
			case SDLK_UP:
				SDL_UpdateWindowSurface(app.window);
			default:
				break;
			}
		} 
	}
	
	SDL_FreeSurface(helloWorld);
	helloWorld = NULL;
	app.Close();

	return 0;
}



