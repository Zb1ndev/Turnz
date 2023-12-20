#include <SDL2/SDL.h>
#include <GLAD/glad.h>

#include <iostream>
#include <vector>

#include "application.h"
#include "../renderer/renderer.h"
#include "../input/input.h"

Application* Application::instance;
Renderer::Scene* Application::currentScene;

const char* Application::Init(const char* title, int w, int h) {

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return "Failed to Initialize SLD2";

	// Setup OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Create Window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE| 
		SDL_WINDOW_KEYBOARD_GRABBED | SDL_WINDOW_MOUSE_CAPTURE | SDL_WINDOW_OPENGL
	);
	if (window == NULL) return "Failed to Create Window";

	// From Window, Create GL Context
	glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL) return "Failed to grab OpenGL Context";
	
	// Get All OpenGL functions
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) return "GLAD was not initialized";

	// Initialize Input States
	Input::InitKeyStates();

	return "Finished Initializing";

}

void Application::Close() {

	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();

}
void Application::UpdateWindowProperties() {
	SDL_GetWindowSize(instance->window, &instance->width, &instance->height);
}


Application::Application(
	const char* title,
	int w, int h,
	std::string vertexShaderDirectory,
	std::string fragmentShaderDirectory,
	Renderer::Scene scene,
	void (*startPointer)(), 
	void (*updatePointer)(), 
	void (*onClosePointer)()
) { 

	instance = this;
	currentScene = &scene;

	std::cout << Init(title, w, h) << "\n"; // Initialize SDL2 and ( OpenGL / GLAD )

	renderer = Renderer(
		vertexShaderDirectory, 
		fragmentShaderDirectory
	); // Create Renderer and Pass in Shader files

	renderer.CreateGraphicsPipline(); // Compile and Bind Shaders
	renderer.PreDraw();

	if(startPointer!=NULL) startPointer(); // Run Start Function

	while (!Input::keyStates[Input::QUIT]) {
		UpdateWindowProperties();
		Input::UpdateInput();
		if (updatePointer != NULL) updatePointer(); // Run Update Function
		renderer.Draw(); // Draw to the Screen
		SDL_GL_SwapWindow(window); // Swap Buffers
	}

	if (onClosePointer != NULL) onClosePointer(); // Run OnClose Function
	Close(); // Close down the App
}
Application::~Application(){}

