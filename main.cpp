//静态链接
#define GLEW_STATIC
#pragma comment(lib,"opengl32.lib")
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <windows.h>
#include <iostream>
#include <string>

#include "Shader.h"
#include "Game.h"
#include "Resource Manager.h"

GLchar sWindowName[] = "Thunder";
GLfloat deltaTime = 0.0f;   // 当前帧遇上一帧的时间差
GLfloat lastFrame = 0.0f;   // 上一帧的时间

Game BreakOut(nWindowWidth, nWindowHeight);

void KeyboardFunc(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//std::cout << key << "\n";
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			BreakOut.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			BreakOut.Keys[key] = false;
	}
}

int main() {
	//GLFW是专门针对OpenGL的语言库
	//主版本号3
	//次版本号3
	//核心模式
	//不允许调整窗口大小
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(nWindowWidth, nWindowHeight, sWindowName, nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to creat window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLEW用来管理OpenGL函数指针，调用任何OpenGL函数之前应该初始化GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		return -1;
	}
	glGetError();

	//键盘输入控制
	glfwSetKeyCallback(window, KeyboardFunc);

	glViewport(0, 0, nWindowWidth, nWindowHeight);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BreakOut.Init();
	BreakOut.state = ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		BreakOut.ProcessInput(deltaTime);
		BreakOut.Update(deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (BreakOut.state == WIN) {
			std::cout << "WIN" << std::endl;
			//break;
		}
		else if (BreakOut.state == LOSS) {
			std::cout << "LOSS" << std::endl;
			//break;
		}
		else {
			BreakOut.Render();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ResourceManager::Clear();
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}