#include "Level.h"
void Level::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight) {
	Bricks.clear();
	unsigned int tileCode;
	Level level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;
	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode) {
				row.emplace_back(tileCode);
			}
			tileData.emplace_back(row);
		}
		if (tileData.size()) {
			this->Init(tileData, levelWidth, levelHeight);
		}
	}
}

void Level::Draw(SpriteRender &render) {
	for (auto &item : Bricks) {
		if (!item.Destroyed) {
			item.Draw(render);
		}
	}
}

bool Level::IsCompleted() {
	for (auto &tile : Bricks) {
		if (!tile.IsSolid && !tile.Destroyed) {
			return false;
		}
		return true;
	}
}

void Level::Init(std::vector<std::vector<unsigned int>> tileData,
	unsigned int levelWidth,unsigned int levelHeight) {

	unsigned height = tileData.size();
	unsigned width = tileData[0].size();
	float uint_width = levelWidth / static_cast<float>(width);
	float uint_height = levelHeight / static_cast<float>(height);
	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			glm::vec2 pos(uint_width * x, uint_height * y);
			glm::vec2 size(uint_width, uint_height);
			if (tileData[y][x] == 1) {
				GameObject obj(pos, size, ResourceManager::GetTexture("block_solid")
					, glm::vec3(0.8, 0.8, 0.7));
				obj.IsSolid = true;
				Bricks.emplace_back(obj);
			}
			else if (tileData[y][x] > 1) {
				glm::vec3 color(1.0f);
				if (tileData[y][x] == 2) {
					color = glm::vec3(0.2f, 0.6f, 1.0f);
				}
				if (tileData[y][x] == 3) {
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				}
				if (tileData[y][x] == 4) {
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				}
				if (tileData[y][x] == 5) {
					color = glm::vec3(1.0f, 0.5f, 0.0f);
				}

				GameObject obj(pos, size, ResourceManager::GetTexture("block")
					, color);
				Bricks.emplace_back(obj);
			}
		}
	}
}