#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件
#include "Shader.h"
#include "Texture.h"
class SpriteRender {
public:
	SpriteRender(const Shader& s);
	~SpriteRender();

	void DrawSprite(const Texture2D& texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10), GLfloat rotate = 0, glm::vec3 color = glm::vec3(1));
private:
	Shader shader;
	GLuint quadVAO;
	void InitRenderData();
};
