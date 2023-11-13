#include <iostream>
#include <SDL.h>

int main(int argc, char** argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
		std::cerr << "SDL failed to initialize";
	if (SDL_CreateWindow("Turnz | By : Joel Zbinden", 0, 0, 640, 480, SDL_WINDOW_OPENGL) != 0)
		std::cerr << "SDL window failed to open";
	


	return 0;

}