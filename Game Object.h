#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include "Sprite Render.h"


class GameObject {
public:
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	//	为1代表不可摧毁
	bool IsSolid;
	bool Destroyed;

	Texture2D Sprite;


	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
		glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0));
	virtual void Draw(SpriteRender &render);
};