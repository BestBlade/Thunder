#pragma once
#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Game Object.h"
struct Particle {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle() {
		Position = glm::vec2(0.0f);
		Velocity = glm::vec2(0.0f);
		Color = glm::vec4(1.0f);
		Life = 0;
	}
};

class ParticleGenerator {
public:
	ParticleGenerator(Shader s, Texture2D tex, GLuint amount);

	void Update(GLfloat dt, GameObject& object, GLuint newParticles
		, glm::vec2 offset = glm::vec2(0));

	void Draw();
private:
	std::vector<Particle> particles;
	unsigned int amount;
	Shader shader;
	Texture2D texture;
	unsigned int VAO;
	void Init();
	unsigned int firstUnusedParticle();
	void respawnParticle(Particle& particle, GameObject& obj,
		glm::vec2 offset = glm::vec2(0));
};