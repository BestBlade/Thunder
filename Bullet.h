#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include "Sprite Render.h"
#include "Game Object.h"

#define BULLETSPEED glm::vec2(550, 0)
#define MYBULLETSIZE 20.0f
#define ENEMYBULLETSIZE 10.0f

class Bullet :public GameObject {
public:
	float Radius;
	bool Destroyed;

	Bullet();
	Bullet(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D texture);

	glm::vec2 Move(float dt, unsigned int window_width, unsigned int window_height);
	void SetExist(bool status);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};