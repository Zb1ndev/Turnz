#include <SDL.h>
#include <iostream>

#include "input/input.h"
#include "application/application.h"
#include "renderer/renderer.h"

int main(int argc, char** argv) {

	Application app = Application("Turnz", 640, 480);
	while (!Input::GetInput(Input::KeyCode::QUIT)) {
		Update();
		Renderer::Render();
		SDL_GL_SwapWindow(app.window); 
	} 
	app.Close();
	return 0;

}

void Update() {



}



