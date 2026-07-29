#include "tgpch.h"

#include "Core.h"
#include "Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//========= FUNC DEFINITIONS ============//
void TGprocessInput(GLFWwindow* window);
void TGWindowSizeCallback(GLFWwindow* window, int width, int height);

struct WindowSpecifications
{
	int width;
	int height;
	const char* title;

	//Won't be used until I understand what they mean :)
	GLFWmonitor* monitor;
	GLFWwindow* share;
};

WindowSpecifications windowSpec = { 800, 600, "templeGraphics", nullptr, nullptr };

int main()
{
	templeG::Log::Init();

	int success = glfwInit();
	TG_ASSERT(success, "GLFW Init Failed!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowSpec.width, windowSpec.height, windowSpec.title, windowSpec.monitor,  windowSpec.share);
	if (window == NULL)
	{
		TG_ERROR("Failed to create GLFW Window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		TG_ERROR("Failed to initialize GLAD");
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, TGWindowSizeCallback);
	while (!glfwWindowShouldClose(window))
	{
		TGprocessInput(window);
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void TGprocessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void TGWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	TG_INFO("Size Callback: Prev [({}, {})]  Now [({}, {})]", windowSpec.width, windowSpec.height, width, height);
	windowSpec.width = width;
	windowSpec.height = height;
	glViewport(0, 0, windowSpec.width, windowSpec.height);
}