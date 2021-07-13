#pragma once
#include <vector>
#include <glm/glm.hpp>
#include"Game Object.h"
#include"Sprite Render.h"
#include"Resource Manager.h"

class Level {
public:
	std::vector<GameObject> Bricks;
	Level() {};
	void Load(const char* filepath, unsigned int levelWidth, unsigned int levelHeight);
	void Draw(SpriteRender& render);
	bool IsCompleted();
private:
	void Init(std::vector<std::vector<unsigned int>> titleData,
		unsigned int levelWidth, unsigned int levelHeight);
};