#include <SDL2/SDL.h>
#include <GLAD/glad.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "renderer.h"
#include "../application/application.h"

Renderer::Renderer(std::string vertShaderDir, std::string fragShaderDir) {
	gVertShaderDir = vertShaderDir;
	gFragShaderDir = fragShaderDir;
}
void Renderer::Render(GLsizei height, GLsizei width) {
	Draw(height, width);
}
void Renderer::Draw(GLsizei height, GLsizei width) {



	// Pre Draw
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glViewport(0, 0, height, width);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(gGPShaderProgram);

	// Draw
	glBindVertexArray(gVertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
	// glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(
		GL_TRIANGLES, 
		10, // Change to Scene.GetVerticies.size
		GL_UNSIGNED_INT, 
		(void*)0
	);

}

void Renderer::VertexSpecification() {

	const std::vector<GLfloat> vertexData{

		-0.5f, -0.5f, 0.0f,  // 0 | Position
		 1.0f, 0.0f, 0.0f,   // 0 | Color

		 0.5f, -0.5f, 0.0f,  // 1 | Position
		 0.0f, 1.0f, 0.0f,   // 1 | Color

		 -0.5f,  0.5f, 0.0f, // 2 | Position
		 0.0f, 0.0f, 1.0f,   // 2 | Color 

		 0.5f, 0.1f, 0.0f,   // 3 | Position
		 0.0f, 1.0f, 1.0f,   // 3 | Color

		 -0.5f, -0.5f, 0.0f,  // 4 | Position
		 1.0f, 0.0f, 0.0f,   // 4 | Color

		 0.9f, 0.9f, 0.0f,  // 5 | Position
		 0.0f, 1.0f, 0.0f,   // 5 | Color

		 0.95f,  0.9f, 0.0f, // 6 | Position
		 0.0f, 0.0f, 1.0f,   // 6 | Color 

		 0.9f, 0.95f, 0.0f,   // 7 | Position
		 0.0f, 1.0f, 1.0f,   // 7 | Color

	};

	glGenVertexArrays(1, &gVertexArrayObject);
	glBindVertexArray(gVertexArrayObject);

	glGenBuffers(1, &gVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

	glBufferData(
		GL_ARRAY_BUFFER,
		vertexData.size() * sizeof(GLfloat),
		vertexData.data(),
		GL_DYNAMIC_DRAW
	);

	const std::vector<GLuint> indexBufferData {
		2,0,1, 
		3,2,1,
		5,6,7
	};

	glGenBuffers(1, &gIndexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indexBufferData.size() * sizeof(GLuint),
		indexBufferData.data(),
		GL_DYNAMIC_DRAW
	);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (void*)0);

	glEnableVertexAttribArray(1); // Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (void*)(sizeof(GL_FLOAT) * 3));

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

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

