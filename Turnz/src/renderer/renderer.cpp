#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include <iostream>
#include <vector>

#include "renderer.h"
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
	glDrawArrays(GL_TRIANGLES, 0, 3);


}
void Renderer::VertexSpecification() {

	const std::vector<GLfloat> vertexPositions{
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f,
	};

	glGenVertexArrays(1, &gVertexArrayObject);
	glBindVertexArray(gVertexArrayObject);
	
	glGenBuffers(1, &gVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

	glBufferData(
		GL_ARRAY_BUFFER,
		vertexPositions.size() * sizeof(GLfloat),
		vertexPositions.data(),
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

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
void Renderer::CreateGraphicsPipline() {

	const char* vs = "#version 410 core\n"
					 "in vec4 position;\n"
					 "void main()\n"
					 "{\n"
					 "	gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
					 "}\n";
	const char* fs = "#version 410 core\n"
					 "out vec4 color;\n"
					 "void main()\n"
					 "{\n"
					 "	color = vec4(1.0f,1.0f,1.0f,1.0f);\n"
					 "}\n";

	gGPShaderProgram = CreateShaderProgram(vs, fs);

}
void Renderer::Render(GLsizei height, GLsizei width) {
	Draw(height,width);
}
