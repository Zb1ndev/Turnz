#pragma once
#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include <iostream>
#include <string>

class Renderer {

public:

	Renderer() = default;
	Renderer(std::string vertShaderDir, std::string fragShaderDir);
	void Render(GLsizei height, GLsizei width);
	void VertexSpecification();
	void CreateGraphicsPipline();

private:

	GLuint gVertexArrayObject = 0;
	GLuint gVertexBufferObject = 0;
	GLuint gGPShaderProgram = 0;

	std::string gVertShaderDir;
	std::string gFragShaderDir;

	std::string LoadShaderFromFile(std::string fileDir);
	GLuint CompileShader(GLuint type, const char* shaderSource);
	GLuint CreateShaderProgram(const char* vertexShader, const char* fragmentShader);
	void Draw(GLsizei height, GLsizei width);

};