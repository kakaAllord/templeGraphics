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

	TG_ASSERT(glfwInit(), "GLFW Init Failed!");

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

	glViewport(0, 0, windowSpec.width, windowSpec.height);
	glfwSetWindowSizeCallback(window, TGWindowSizeCallback);


	//=========== All other code comes here ========================//

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main() {\n"
		"gl_Position = vec4(aPos, 1.0f);\n"
		"}\n";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int success;
	const int infoLog_L = 512;
	char infoLog[infoLog_L];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, infoLog_L, NULL, infoLog);
		TG_ERROR("Vertex Shader Compilation Failed: {}", infoLog);
	}

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, infoLog_L, NULL, infoLog);
		TG_ERROR("Fragment Shader Compilation Failed: {}", infoLog);
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, infoLog_L, NULL, infoLog);
		TG_ERROR("Shader program link Failed: {}", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window))
	{
		TGprocessInput(window);
		glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);



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