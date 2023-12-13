#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <vector>

#include "input/input.h"
#include "application/application.h"
#include "renderer/renderer.h"

Renderer::Scene::GameObject* cube;
Renderer::Scene::GameObject* cube2;

float speed = 0.0005f;
float cube1Velocity = 0.0f;
float cube2Velocity = 0.0f;

void Start() {

}

void Update() {

	cube1Velocity = (cube->position.y > -0.7f) ? cube1Velocity + -0.0000004f : 0;
	if (cube1Velocity == 0 && Input::keyStates[Input::SPACE]) cube1Velocity = 0.0005f;
	
	// Move Cube 1
	cube->position = glm::vec3(
		Input::keyStates[Input::D] ? cube->position.x + speed : Input::keyStates[Input::A] ? cube->position.x - speed : cube->position.x,
		cube->position.y + cube1Velocity,
		0
	);

	// Move Cube 2
	cube2Velocity = (cube2->position.y > -0.7f) ? cube2Velocity + -0.0000004f : 0;
	cube2->position = glm::vec3(
		cube2->position.x,
		cube2->position.y + cube2Velocity,
		0
	);

}

void OnClose() {

}

Renderer::Scene SceneInit() {

	Renderer::Scene result = Renderer::Scene (
		std::vector <Renderer::Scene::GameObject> {
			Renderer::Scene::GameObject (
				"Test1",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				std::vector<GLfloat> {

						-0.1f, -0.3f, 0.0f,  // 0 | Position
						1.0f, 1.0f, 1.0f,   // 0 | Color

						0.1f, -0.3f, 0.0f,  // 1 | Position
						1.0f, 1.0f, 1.0f,   // 1 | Color

						-0.1f,  0.3f, 0.0f, // 2 | Position
						1.0f, 1.0f, 1.0f,  // 2 | Color 

						0.1f, 0.3f, 0.0f,   // 3 | Position
						1.0f, 1.0f, 1.0f,   // 3 | Color

				},
				std::vector<GLuint> {
					2,0,1,
					3,2,1
				}
			),
			Renderer::Scene::GameObject(
				"Test2",
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				std::vector<GLfloat> {

					-0.1f, -0.3f, 0.0f,  // 0 | Position
					1.0f, 1.0f, 1.0f,   // 0 | Color

					0.1f, -0.3f, 0.0f,  // 1 | Position
					1.0f, 1.0f, 1.0f,   // 1 | Color

					-0.1f, 0.3f, 0.0f, // 2 | Position
					1.0f, 1.0f, 1.0f,  // 2 | Color 

					0.1f, 0.3f, 0.0f,   // 3 | Position
					1.0f, 1.0f, 1.0f,   // 3 | Color

				},
				std::vector<GLuint> {
					6, 4, 5,
					7, 6, 5
				}
			)
		}
	);

	cube = &result.hierarchy[0];
	cube2 = &result.hierarchy[1];

	return result;

}
int main(int argc, char** argv) {
	Application app = Application(
		"Turnz",
		1280, 720,
		"./Turnz/Turnz/src/shaders/vertex.glsl",
		"./Turnz/Turnz/src/shaders/fragment.glsl",
		SceneInit(),
		&Start,
		&Update,
		&OnClose
	);
	return 0;
}
