#include "Game.h"
#include "Resource Manager.h"
#include "Sprite Render.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int pre = 0;
int time = 0;
bool crush;

Game::Game(GLuint w, GLuint h) {
	width = w;
	height = h;
}
Game::~Game() {
	delete this->Renderer;
}
void Game::Init() {
	ResourceManager::LoadShader("./shaders/object.vs", "./shaders/object.frag", nullptr, "Sprite");
	ResourceManager::LoadShader("./shaders/particle.vs", "./shaders/particle.frag", nullptr, "particle");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width),
		static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("Sprite").Use().setInt("image", 0);
	ResourceManager::GetShader("Sprite").setMatrix4("proj", projection);
	ResourceManager::GetShader("particle").Use().setInt("Sprite", 0);
	ResourceManager::GetShader("particle").setMatrix4("proj", projection);
	// Set render-specific controls
	this->Renderer = new SpriteRender(ResourceManager::GetShader("Sprite"));
	// Load textures
	ResourceManager::LoadTexture("./textures/fire1.png", GL_TRUE, "bullet1");
	ResourceManager::LoadTexture("./textures/fire2.png", GL_TRUE, "bullet2");
	ResourceManager::LoadTexture("./textures/block.png", false, "block");
	ResourceManager::LoadTexture("./textures/enemy.png", true, "enemy");
	ResourceManager::LoadTexture("./textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("./textures/plane.png", true, "player");
	ResourceManager::LoadTexture("./textures/particle.png", true, "particle");
	//	·É»ú³õÊ¼Î»ÖÃ
	glm::vec2 playerPos = glm::vec2(
		PLAYERSIZE.x / 2.0f,
		this->height * 0.5 - PLAYERSIZE.y * 0.5
	);
	Player = new Plane(playerPos, PLAYERSIZE,
		ResourceManager::GetTexture("player"), glm::vec3(0, 1, 0));

	Particles = new ParticleGenerator(ResourceManager::GetShader("particle"),
		ResourceManager::GetTexture("particle"), 500);

	ResetEnemy();
}
void Game::ProcessInput(GLfloat dt) {
	if (this->state == ACTIVE && !Player->Destroyed) {
		float v = PLAYERVELOCITY * dt;
		if (this->Keys[GLFW_KEY_A]) {
			if (Player->Position.x >= 0) {
				Player->Position.x -= v;
			}
		}
		if (this->Keys[GLFW_KEY_D]) {
			if (Player->Position.x <= this->width*0.5 - Player->Size.x) {
				Player->Position.x += v;
			}
		}
		if (this->Keys[GLFW_KEY_W]) {
			if (Player->Position.y >= 0) {
				Player->Position.y -= v;
			}
		}
		if (this->Keys[GLFW_KEY_S]) {
			if (Player->Position.y <= this->height - Player->Size.y) {
				Player->Position.y += v;
			}
		}
		if (this->Keys[GLFW_KEY_J]) {
			if (time - pre >= 0.0001) {
				Player->Attack();
				pre = time;
			}
		}
		if (this->Keys[GLFW_KEY_U]) {
			crush = 1;
		}
		else {
			crush = 0;
		}
	}
}

void Game::Update(GLfloat dt) {
	time = glfwGetTime();
	
	if (Player->Destroyed || planes.empty()) {
		if (Player->Destroyed) {
			state = LOSS;
		}
		else {
			state = WIN;
		}
		return;
	}
	if (rand() % 100 < 2) {
		for (auto& enemy : planes) {
			enemy->Attack();
		}
	}


	DoCollisions();

	for (auto &b:Player->bullets) {
		b->Move(dt, nWindowWidth, nWindowHeight);
		if (b->Destroyed) {
			Player->bullets.erase(b);
			continue;
		}
	}
	for (auto &enemy:planes) {
		enemy->Move(dt, nWindowWidth, nWindowHeight);
		for (auto& b : enemy->bullets) {
			b->Move(dt, nWindowWidth, nWindowHeight);
			if (b->Destroyed) {
				enemy->bullets.erase(b);
			}
		}
		if (enemy->Destroyed) {
			planes.erase(enemy);
			continue;
		}
	}
	Particles->Update(dt, *Player, 2, glm::vec2(Player->Radius * 0.5));
}

void Game::Render() {	

	Renderer->DrawSprite(ResourceManager::GetTexture("background"),
		glm::vec2(0.0f), glm::vec2(this->width, this->height), 0.0f);

	Player->Draw(*Renderer);

	if (this->state == ACTIVE) {
		for (auto& b : Player->bullets) {
			b->Draw(*Renderer);
		}
		for (auto iter = planes.begin(); iter != planes.end(); ++iter) {
			auto enemy = *iter;
			enemy->Draw(*Renderer);
			for (auto& b : enemy->bullets) {
				b->Draw(*Renderer);
			}
		}
	}

	Particles->Draw();
}

void Game::ResetPlayer() {
	Player->Size = PLAYERSIZE;
	Player->Position = glm::vec2(this->width / 2.0f - PLAYERSIZE.x / 2.0f, this->height - PLAYERSIZE.y);
}

void Game::ResetEnemy() {
	for (int i = 0; i <= MAXENEMY; ++i) {
		glm::vec2 pos = glm::vec2(
			nWindowWidth * 0.45 + rand() % (int)(nWindowWidth * 0.5),
			nWindowHeight * 0.05 + rand() % (int)(nWindowHeight * 0.9)
		);
		glm::vec2 velocity = glm::vec2(
			300 * ((rand() % 9999) / 5000.f - 1),
			300 * ((rand() % 9999) / 5000.f - 1)
		);
		planes.emplace(new Enemy(pos, EnemySIZE.y, velocity,
			ResourceManager::GetTexture("enemy"), glm::vec3(0, 1, 0)));
	}
}

bool CheckCollision(Bullet & first, Enemy& second) {
	//	R && AABB
	// get center point circle first 
	glm::vec2 center1(first.Position + first.Radius);
	glm::vec2 center2(second.Position + second.Radius);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(second.Size.x / 2.0f, second.Size.y / 2.0f);
	glm::vec2 aabb_center(
		second.Position.x + aabb_half_extents.x,
		second.Position.y + aabb_half_extents.y
	);
	// get difference vector between both centers
	glm::vec2 difference = center1 - center2;

	if (glm::length(difference) <= first.Radius + second.Radius) {
		return true;
	}
	return false;
}

bool CheckCollision(Plane& first, Enemy& second) {
	//	R && AABB
	// get center point circle first 
	glm::vec2 center(second.Position + second.Radius);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(first.Size.x * 0.5f, first.Size.y * 0.5f);
	glm::vec2 aabb_center = first.Position + aabb_half_extents;
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < second.Radius;
}

bool CheckCollision(Plane& first, Bullet& second) {
	//	R && AABB
	// get center point circle first 
	glm::vec2 center(second.Position + second.Radius);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(first.Size.x * 0.5f, first.Size.y * 0.5f);
	glm::vec2 aabb_center = first.Position + aabb_half_extents;
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;
	return glm::length(difference) < second.Radius;
}

void Game::DoCollisions() {
	for (auto& b : Player->bullets) {
		for (auto& enemy : planes) {
			if (!enemy->Destroyed) {
				bool coll = CheckCollision(*b, *enemy);
				if (coll) {
					b->Destroyed = true;
					enemy->Life -= 1;
					if (enemy->Life == 2) {
						enemy->Color = glm::vec3(1, 1, 0);
					}
					else if (enemy->Life == 1) {
						enemy->Color = glm::vec3(1, 0, 0);
					}
					else if (enemy->Life == 0) {
						enemy->Destroyed = true;
					}
				}
			}
		}
	}

	for (auto& enemy : planes) {
		bool coll = CheckCollision(*Player, *enemy);
		if (coll) {
			std::cout << "Hit" << std::endl;
			Player->Life = 0;
			Player->Destroyed = true;

			if(Player->Life <= 1) {
				Player->Color = glm::vec3(1, 0, 0);
			}
		}
	}

	if (crush) {
		for (auto& enemy:planes) {
			for (auto& b : enemy->bullets) {
				b->Destroyed = true;
			}
			enemy->Destroyed = true;
		}
	}

	for (auto& enemy : planes) {
		for (auto& b : enemy->bullets) {
			bool coll = CheckCollision(*Player, *b);
			if (coll) {
				Player->Life -= 1;
				b->Destroyed = true;
				if (Player->Life == 2) {
					Player->Color = glm::vec3(1, 1, 0);
				}
				if (Player->Life <= 1) {
					Player->Color = glm::vec3(1, 0, 0);
				}
				if (Player->Life <= 0) {
					Player->Destroyed = true;
				}
			}
		}
	}
}