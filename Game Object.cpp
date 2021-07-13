#include "Game Object.h"
GameObject::GameObject() {
	this->Position = glm::vec2(0);
	this->Size = glm::vec2(1.0);
	this->Velocity = glm::vec2(0.f);

	this->Color = glm::vec3(1.0f);
	this->IsSolid = false;
	this->Destroyed = false;
	this->Rotation = 0;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size,
	Texture2D tex, glm::vec3 color, glm::vec2 v) {
	Position = pos;
	Size = size;
	this->Sprite = tex;
	Color = color;
	Velocity = v;
	IsSolid = false;
	Destroyed = false;
	Rotation = 0;
}

void GameObject::Draw(SpriteRender& render) {
	render.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}