#include <SDL2/SDL.h>
#include <GLAD/glad.h>

#include <iostream>

#include "input/input.h"
#include "application/application.h"
#include "renderer/renderer.h"

void Start() {

	

}

bool filled = true;
void Update() {

	if (Input::GetInput(Input::A))
		filled = !filled;
	glPolygonMode(GL_FRONT, filled ? GL_LINE : GL_FILL);
	
}

void OnClose() {



}

int main(int argc, char** argv) {

	Application app = Application(
		"Turnz", 
		640, 480, 
		"./Turnz/Turnz/src/shaders/vertex.glsl",
		"./Turnz/Turnz/src/shaders/fragment.glsl",
		&Start, 
		&Update, 
		&OnClose
	);

	return 0;

}