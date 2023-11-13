#include <iostream>
#include <string>
#include <SDL.h>

#include "math/math.h"

using namespace Math;



int main(int argc, char** argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		std::cerr << "SDL failed to initialize \n";
	if (SDL_CreateWindow("Turnz | By : Joel Zbinden", 200, 200, 640, 480, SDL_WINDOW_OPENGL) == 0)
		std::cerr << "SDL window closed \n";

	return 0;

}



