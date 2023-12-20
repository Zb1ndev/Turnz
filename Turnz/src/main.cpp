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

float rotationSpeed = 0.15f;
float speed = 0.0005f;
float jumpVel = 0.001f;
float vel = 0.0f;

void Start() {
	
}

void Update() {

	vel = (cube->position.y > (-1.0f + (cube->scale.y / 20))) ? vel + -0.0000009f : 0;
	if (vel == 0 && (Input::keyStates[Input::SPACE] || Input::keyStates[Input::W])) vel = jumpVel;
	if ((cube->position.y > (-1.0f + (cube->scale.y / 20)))) {
		cube->rotation = glm::vec4(
			0.0f,
			0.0f,
			Input::keyStates[Input::A] ? cube->rotation.z + rotationSpeed : Input::keyStates[Input::D] ? cube->rotation.z - rotationSpeed : cube->rotation.z - rotationSpeed,
			1.0f
		);
	} else {
		cube->rotation = glm::vec4(0.0f);
	}

	cube->position = glm::vec3 (
		Input::keyStates[Input::D] ? cube->position.x + speed  : Input::keyStates[Input::A] ? cube->position.x - speed : cube->position.x,
		cube->position.y + vel,
		0
	);

	if (Input::keyStates[Input::F]) {
		cube->position = glm::vec3 (
			Input::MousePosToViewPort().x,
			Input::MousePosToViewPort().y,
			0
		);
	}

}

void OnClose() {

}

Renderer::Scene SceneInit() {

	Renderer::Scene result = Renderer::Scene (
		std::vector <Renderer::Scene::GameObject> {
			Renderer::Scene::GameObject(
				"Test",
				glm::vec3(0.0f,0.0f,0.0f),
				glm::vec3(1.0f,1.0f,1.0f),
				glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
				std::vector<glm::vec4> {
					glm::vec4(-0.3f, -0.3f, 0.0f, 1.0f),
					glm::vec4(0.3f, -0.3f, 0.0f, 1.0f),
					glm::vec4(-0.3f, 0.3f, 0.0f, 1.0f),
					glm::vec4(0.3f, 0.3f, 0.0f, 1.0f)
				},
				std::vector<glm::vec4> {
					glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
					glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
					glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
					glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
				},
				std::vector<GLuint> {
					0,1,2,
					1,3,2
				}
			)
		}
	);

	cube = &result.hierarchy[0];
	return result;
	
}
int main(int argc, char** argv) {
	Application app = Application(
		"Turnz",
		600, 600,
		"./Turnz/Turnz/src/vertex.glsl",
		"./Turnz/Turnz/src/fragment.glsl",
		SceneInit(),
		&Start,
		&Update,
		&OnClose
	);
	return 0;
}
