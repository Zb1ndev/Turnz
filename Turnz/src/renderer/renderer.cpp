#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../input/input.h"
#include "renderer.h"
#include "../application/application.h"

Renderer::Scene::GameObject::GameObject(){}
Renderer::Scene::GameObject::GameObject(const char* kName,glm::vec3 kPosition,glm::vec3 kScale,std::vector<GLfloat> kVertexData,std::vector<GLuint> kIndexBufferData) {
	name = kName;
	position = kPosition;
	scale = kScale;
	vertexData = kVertexData;
	indexBufferData = kIndexBufferData;
}
std::vector<GLfloat> Renderer::Scene::GameObject::GetVertexData() {

	// To-do : make it so you can rotate and scale shit, also make it automatically do the IndexBufferData shit

	size_t rowCounter = 0;
	size_t size = this->vertexData.size() / 2;
	std::vector<size_t> indexes;

	for (size_t i = 0; i < size; i++) {
		if (i == 0) indexes.push_back(0);
		else {
			if ((i % 3) == 0)
				rowCounter++;
			indexes.push_back(i + (rowCounter * 3));
		}
	}
	size_t indexSize = indexes.size();

	int counter = 0;
	std::vector<GLfloat> transformedVertexData = vertexData;
	for (size_t i = 0; i < indexes.size(); i++){
		counter++;
		if (counter == 1) transformedVertexData[indexes[i]] = (position.x) + vertexData[indexes[i]];
		if (counter == 2) transformedVertexData[indexes[i]] = (position.y) + vertexData[indexes[i]];
		if (counter == 3) transformedVertexData[indexes[i]] = (position.z) + vertexData[indexes[i]];
		if (counter == 3) counter = 0;
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

Renderer::Renderer(std::string vertShaderDir, std::string fragShaderDir, GLsizei height, GLsizei width) {
	gVertShaderDir = vertShaderDir;
	gFragShaderDir = fragShaderDir;
	gHeight = height;
	gWidth = width;
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

}
void Renderer::Draw() {

	glViewport(0, 0, gHeight, gWidth);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	VertexSpecification();

	glDrawElements(
		GL_TRIANGLES, 
		Application::instance->currentScene->GetVerticies() + (Application::instance->currentScene->GetVerticies() / 2) + 2,
		GL_UNSIGNED_INT, 
		(void*)0
	);

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
