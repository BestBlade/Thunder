#pragma once
#include "Game Object.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include "Sprite Render.h"
#include "Resource Manager.h"
#include "Bullet.h"
#include <vector>
#include <deque>
#include <unordered_set>
class Enemy;

class Plane : public GameObject {
public:
	float Radius;
	bool Destroyed;
	unsigned int Life;
	std::unordered_set<Bullet*> bullets;

	Plane();
	Plane(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color = glm::vec3(1.0f));

	glm::vec2 Move(float dt, unsigned int window_width, unsigned int window_height);
	void Attack();
	void GodHandCrush();
	void Draw(SpriteRender& render);
	void Reset(glm::vec2 pos, glm::vec2 velocity);
};


class Enemy :public GameObject {
public:
	float Radius;
	bool Destroyed;
	unsigned int Life;

	std::unordered_set<Bullet*> bullets;

	Enemy();

	Enemy(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D texture, glm::vec3 color);
	
	glm::vec2 Move(float dt, unsigned int window_width, unsigned int window_height);
	void Attack();
	void Draw(SpriteRender& render);
};