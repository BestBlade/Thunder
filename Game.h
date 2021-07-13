#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <deque>
#include <unordered_set>
#include "Sprite Render.h"
#include "Level.h"
#include "Bullet.h"
#include "Plane.h"
#include "Particle.h"

#define nWindowWidth 1280.0f
#define nWindowHeight 720.0f
#define MAXENEMY 5
#define CRUSH 100
enum GameState { MENU, ACTIVE, WIN ,LOSS};
enum Direction { UP, DOWN, LEFT, RIGHT };

const glm::vec2 PLAYERSIZE(75, 45);
const glm::vec2 EnemySIZE(100, 50);
const float PLAYERVELOCITY = 500;
// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;
class Game {
public:
	GameState state;
	GLboolean Keys[1024];
	GLuint width, height;
	unsigned int level;
	std::vector<Level> levels;
	std::unordered_set<Enemy*> planes;

	SpriteRender* Renderer;
	Plane* Player;
	ParticleGenerator* Particles;

	Game(GLuint w, GLuint h);
	~Game();

	void Init();

	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();

	void ResetPlayer();
	void ResetEnemy();
};