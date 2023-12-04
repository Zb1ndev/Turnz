#pragma once
#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include <iostream>
#include <vector>
#include <string>

class Renderer {
public:

	Renderer() = default;
	Renderer(std::string vertShaderDir, std::string fragShaderDir, GLsizei height, GLsizei width);
	void PreDraw();
	void Draw();
	void VertexSpecification();
	void CreateGraphicsPipline();

private:

	GLuint gVertexArrayObject = 0;
	GLuint gVertexBufferObject = 0;
	GLuint gIndexBufferObject = 0;
	GLuint gGPShaderProgram = 0;

	GLsizei gHeight;
	GLsizei gWidth;

	std::string gVertShaderDir;
	std::string gFragShaderDir;

	std::string LoadShaderFromFile(std::string fileDir);
	GLuint CompileShader(GLuint type, const char* shaderSource);
	GLuint CreateShaderProgram(const char* vertexShader, const char* fragmentShader);
	
};