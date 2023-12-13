#pragma once
#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include <glm/vec3.hpp>

#include <iostream>
#include <vector>
#include <string>

class Renderer {
public:

	class Scene {
	public:

		class GameObject {
		public:

			const char* name;
			glm::vec3 position;
			glm::vec3 scale;

			GameObject();
			GameObject(
				const char* kName,
				glm::vec3 kPosition,
				glm::vec3 kScale,
				std::vector<GLfloat> kVertexData,
				std::vector<GLuint> kIndexBufferData
			);

			std::vector<GLuint> GetIndexBufferData() { return indexBufferData; }
			std::vector<GLfloat> GetVertexData();

		private:

			std::vector<GLfloat> vertexData;
			std::vector<GLuint> indexBufferData;

		};

		std::vector<GameObject> hierarchy;
		GLuint GetVerticies();
		Scene(std::vector<GameObject> kHierarchy);

	};

	GLsizei gHeight;
	GLsizei gWidth;

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

	std::string gVertShaderDir;
	std::string gFragShaderDir;

	std::string LoadShaderFromFile(std::string fileDir);
	GLuint CompileShader(GLuint type, const char* shaderSource);
	GLuint CreateShaderProgram(const char* vertexShader, const char* fragmentShader);
	std::vector<GLfloat> GetAllVertexData();
	std::vector<GLuint> GetAllIndexBufferData();
	
};