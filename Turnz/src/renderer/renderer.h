#pragma once
#include <SDL2/SDL.h>
#include <GLAD/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <string>

class Renderer {
public:

	class Scene {
	public:

		class GameObject {
		public:

			const char* name;
			bool physics = false;

			glm::vec3 position;
			glm::vec3 scale;
			glm::vec4 rotation;

			GameObject();
			GameObject(
				const char* kName,
				glm::vec3 kPosition,
				glm::vec3 kScale,
				glm::vec4 kRotation,
				std::vector<glm::vec4> kVertexPositions,
				std::vector<glm::vec4> kVertexColors,
				std::vector<GLuint> kIndexBufferData
			);

			std::vector<GameObject> collisions;
			bool colliding = false;
			glm::vec3 bounds;

			std::vector<GLuint> indexBufferData;
			std::vector<GLuint> GetIndexBufferData();
			std::vector<GLfloat> GetVertexData();
			bool CompareBounds(GameObject kComp);

		private:

			std::vector<glm::vec4> vertexPositions;
			std::vector<glm::vec4> vertexColors;

		};

		std::vector<GameObject> hierarchy;

		GLuint GetVerticies();
		GameObject GetGameObject(const char* kName);
		Scene(std::vector<GameObject> kHierarchy);
		void CheckCollision();

	};

	static float widthMultiplier;
	static float heightMultiplier;
	Renderer() = default;
	Renderer(std::string vertShaderDir, std::string fragShaderDir);
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