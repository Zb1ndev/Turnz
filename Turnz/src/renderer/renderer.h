#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Renderer {

public:
	static void Render();

private:
	static void PreDraw();
	static void Draw();

};