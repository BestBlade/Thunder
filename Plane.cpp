#include "Plane.h"

Plane::Plane() {
	Life = 3;
	Radius = 50;
	Destroyed = false;
}

Plane::Plane(glm::vec2 pos, glm::vec2 size, Texture2D texture,glm::vec3 color) 
:GameObject(pos, size, texture, color){
	Life = 3;
	Destroyed = false;
}

glm::vec2 Plane::Move(float dt, unsigned int window_width, unsigned int window_height) {
	this->Position += this->Velocity * dt;
	if (Position.x <= 0) {
		Position.x = 0;
	}
	if (Position.x >= window_width - Radius) {
		Position.x = window_width - Radius;
	}
	if (Position.y <= 0) {
		Position.y = 0;
	}
	if (Position.y >= window_height - Radius) {
		Position.y = window_height - Radius;
	}
	return this->Position;
}

void Plane::Draw(SpriteRender& render) {
	render.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
void Plane::Attack() {
	glm::vec2 pos = this->Position;
	pos.x += this->Size.x;
	pos.y += this->Size.y / 2 - MYBULLETSIZE;
	bullets.emplace(new Bullet(pos, MYBULLETSIZE, BULLETSPEED,
		ResourceManager::GetTexture("bullet1")));
}

void Plane::Reset(glm::vec2 pos, glm::vec2 velocity) {
	this->Position = pos;
	this->Velocity = velocity;
}

Enemy::Enemy(){
	Radius = 50;
	Life = 3;
	Destroyed = false;
}

Enemy::Enemy(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D texture, glm::vec3 color)
	:GameObject(pos, glm::vec2(radius * 2), texture, color, velocity) {
	Life = 3;
	Radius = radius;
	Destroyed = false;
}

glm::vec2 Enemy::Move(float dt, unsigned int window_width, unsigned int window_height) {
	this->Position += this->Velocity * dt;
	if (this->Position.x <= window_width * 0.3 || this->Position.x >= window_width - this->Size.x) {
		this->Velocity.x = -this->Velocity.x;
	}
	if (this->Position.y <= 0 || this->Position.y >= window_height - this->Size.y) {
		this->Velocity.y = -this->Velocity.y;
	}
	//if (this->Position.x >= window_width || this->Position.x <= 0
	//	|| this->Position.y >= window_height || this->Position.y <= 0) {
	//	Destroyed = true;
	//}
	return this->Position;
}

void Enemy::Attack() {	
	if (!Destroyed) {
		int t = rand() % 100;
		if (t < 50) {
			return;
		}
		glm::vec2 v0(
			0.707*-300,
			0.707*300
		);
		glm::vec2 v1(
			-300,
			0
		);
		glm::vec2 v2(
			0.707 * -300,
			0.707 * -300
		);
		glm::vec2 pos = this->Position;
		pos.x -= ENEMYBULLETSIZE * 2;
		pos.y += this->Size.y / 2 - ENEMYBULLETSIZE;
		bullets.emplace(new Bullet(this->Position, ENEMYBULLETSIZE, v0, ResourceManager::GetTexture("bullet2")));
		bullets.emplace(new Bullet(this->Position, ENEMYBULLETSIZE, v1, ResourceManager::GetTexture("bullet2")));
		bullets.emplace(new Bullet(this->Position, ENEMYBULLETSIZE, v2, ResourceManager::GetTexture("bullet2")));
	}
}

void Enemy::Draw(SpriteRender& render) {
	render.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}
