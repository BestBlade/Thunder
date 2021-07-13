#include "Sprite Render.h"
SpriteRender::SpriteRender(const Shader& s) {
	this->shader = s;
	this->InitRenderData();
}
SpriteRender::~SpriteRender() {
	glDeleteVertexArrays(1, &this->quadVAO);
}
void SpriteRender::DrawSprite(const Texture2D& texture, glm::vec2 position,
	glm::vec2 size, GLfloat rotate, glm::vec3 color) {
	this->shader.Use();
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	//	平移到中心做旋转在平移回去
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.setMatrix4("model", model);
	this->shader.setVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRender::InitRenderData() {
	GLuint VBO;
	GLfloat vertex[] = {
		//pos			//tex
		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f,
		0.0f, 0.0f,		0.0f, 0.0f,

		0.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, 0.0f,		1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}