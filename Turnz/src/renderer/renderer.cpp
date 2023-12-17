#include <SDL2/SDL.h>
#include <GLAD/glad.h>

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../input/input.h"
#include "renderer.h"
#include "../application/application.h"

Renderer::Scene::GameObject::GameObject(){}
Renderer::Scene::GameObject::GameObject(const char* kName,glm::vec3 kPosition,glm::vec3 kScale, glm::vec4 kRotation, std::vector<glm::vec4> kVertexPositions, std::vector<glm::vec4> kVertexColors,std::vector<GLuint> kIndexBufferData) {
	name = kName;
	position = kPosition;
	scale = kScale;
	rotation = kRotation;
	vertexPositions = kVertexPositions;
	vertexColors = kVertexColors;
	indexBufferData = kIndexBufferData;
}
std::vector<GLfloat> Renderer::Scene::GameObject::GetVertexData() {

	int counter = 0;
	std::vector<GLfloat> transformedVertexData;
	glm::mat4 model(1.0f);

	size_t size = vertexPositions.size();
	for (size_t v=0; v<size; v++) {

		glm::vec4 vertex = vertexPositions[(size-1)-v];

		Renderer::widthMultiplier = (1.0f / (float)Application::instance->width) * 100;
		Renderer::heightMultiplier = (1.0f / (float)Application::instance->height) * 100;

		// Scale
		glm::vec3 kScale = glm::vec3(
			scale.x*Renderer::widthMultiplier,
			scale.y*Renderer::heightMultiplier,
			scale.z
		);
		model = glm::scale(glm::mat4(1.0f), kScale);
		vertex = (model * vertex);

		// Rotate
		for (size_t i=0; i<3; i++){
			model = glm::rotate(
				glm::mat4(1.0f), 
				glm::radians(i==0?rotation.x:i==1?rotation.y:rotation.z), 
				glm::vec3(i==0?1:0, i==1?1:0, i==2?1:0)
			);
			vertex = (model * vertex);
		}

		// Translate
		model = glm::translate(glm::mat4(1.0f), position);
		vertex = (model * vertex);

		// Add Transformed Vertex to transformedVertexData
		for (size_t i=0; i<3; i++) {
			transformedVertexData.push_back(i==0? vertex.x:i==1? vertex.y: vertex.z);
		}
		for (size_t i = 0; i < 3; i++) {
			transformedVertexData.push_back(i==0?vertexColors[counter].r:i==1?vertexColors[counter].g:vertexColors[counter].b);
		}

		counter++;

	}

	return transformedVertexData;

}

GLuint Renderer::Scene::GetVerticies() {
	std::vector<GLuint> data = Application::instance->renderer.GetAllIndexBufferData();
	GLuint highest = 0;
	for (GLuint var : data)
		if (var > highest) highest = var;
	return highest;
}
Renderer::Scene::Scene(std::vector<GameObject> kHeirarchy) {
	hierarchy = kHeirarchy;
}

std::vector<GLfloat> Renderer::GetAllVertexData() {

	std::vector<GLfloat> result;
	Scene* scene = Application::currentScene;

	size_t size = 0;
	for (size_t i = 0; i < scene->hierarchy.size(); i++)
		size += scene->hierarchy[i].GetVertexData().size();
	result.resize(size);

	for (size_t i = 0; i < scene->hierarchy.size(); i++) {
		std::vector<GLfloat> kVertexData = scene->hierarchy[i].GetVertexData();
		result.insert(result.end(), kVertexData.begin(), kVertexData.end());
	}

	result.erase(result.begin(), std::next(result.begin(), result.size() / 2));

	return result;

}
std::vector<GLuint> Renderer::GetAllIndexBufferData() {

	std::vector<GLuint> result;
	Scene *scene = Application::currentScene;

	size_t size = 0;
	for (size_t i = 0; i < scene->hierarchy.size(); i++)
		size += scene->hierarchy[i].GetIndexBufferData().size();
	result.resize(size);

	for (size_t i = 0; i < scene->hierarchy.size(); i++) {
		std::vector<GLuint> kIndexBufferData = scene->hierarchy[i].GetIndexBufferData();
		result.insert(result.end(), kIndexBufferData.begin(), kIndexBufferData.end());
	}

	result.erase(result.begin(), std::next(result.begin(), result.size() / 2));
	

	return result;

}


float Renderer::widthMultiplier;
float Renderer::heightMultiplier;

Renderer::Renderer(std::string vertShaderDir, std::string fragShaderDir) {
	gVertShaderDir = vertShaderDir;
	gFragShaderDir = fragShaderDir;
}
void Renderer::PreDraw() {

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glUseProgram(gGPShaderProgram);

	glGenVertexArrays(1, &gVertexArrayObject);
	glBindVertexArray(gVertexArrayObject);

	glGenBuffers(1, &gVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

	glGenBuffers(1, &gIndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (void*)0);

	glEnableVertexAttribArray(1); // Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (void*)(sizeof(GL_FLOAT) * 3));

	std::cout << glGetError() << "\n";

}
void Renderer::Draw() {

	glViewport(0, 0, Application::instance->width, Application::instance->height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	VertexSpecification();

	glDrawElements(
		GL_TRIANGLES, 
		Application::instance->currentScene->GetVerticies() + (Application::instance->currentScene->GetVerticies() / 2) + 2,
		GL_UNSIGNED_INT, 
		(void*)0
	);

	std::cout << glGetError() << "\n";

}
void Renderer::VertexSpecification() {

	const std::vector<GLfloat> vertexData = GetAllVertexData();
	const std::vector<GLuint> indexBufferData = GetAllIndexBufferData();

	glBufferData(
		GL_ARRAY_BUFFER,
		vertexData.size() * sizeof(GLfloat),
		vertexData.data(),
		GL_DYNAMIC_DRAW
	);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indexBufferData.size() * sizeof(GLuint),
		indexBufferData.data(),
		GL_DYNAMIC_DRAW
	);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(gVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

}
GLuint Renderer::CompileShader(GLuint type, const char* shaderSource) {

	GLuint shaderObject = glCreateShader(type);
	glShaderSource(shaderObject, 1, &shaderSource, nullptr);
	glCompileShader(shaderObject);

	return shaderObject;

}
GLuint Renderer::CreateShaderProgram(const char* vertexShader, const char* fragmentShader) {

	GLuint progObj = glCreateProgram();
	GLuint vertShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fragShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(progObj, vertShader);
	glAttachShader(progObj, fragShader);
	glLinkProgram(progObj);

	glValidateProgram(progObj);
	return progObj;

}
std::string Renderer::LoadShaderFromFile(std::string fileDir) {

	std::string result = "";
	std::string line = "";
	std::fstream myFile(fileDir.c_str());
	if (myFile.is_open())
		while (std::getline(myFile, line))
			result += line + "\n";
	myFile.close();
	return result;

}
void Renderer::CreateGraphicsPipline() {
	gGPShaderProgram = CreateShaderProgram(
		LoadShaderFromFile(gVertShaderDir).c_str(),
		LoadShaderFromFile(gFragShaderDir).c_str()
	);
}