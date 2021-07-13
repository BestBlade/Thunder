#include "Bullet.h"
#include <glm/glm.hpp>
#include "Texture.h"
Bullet::Bullet() {
	Radius = MYBULLETSIZE;
	Destroyed = false;
}

Bullet::Bullet(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D texture)
:GameObject(pos, glm::vec2(radius * 2), texture, glm::vec3(1.0f), velocity){
	Destroyed = false;
	Radius = radius;
}

glm::vec2 Bullet::Move(float dt, unsigned int window_width, unsigned int window_height) {
	if (!Destroyed) {
		this->Position += this->Velocity * dt;
	}
	if (this->Position.x >= window_width || this->Position.x < 0 ||
		this->Position.y >= window_height || this->Position.y < 0) {
		Destroyed = true;
	}
	return this->Position;
}

void Bullet::SetExist(bool status) {
	Destroyed = status;
}

void Bullet::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->Position = position;
	this->Velocity = velocity;
	this->Destroyed = false;
}