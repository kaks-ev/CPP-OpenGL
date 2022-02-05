#include <iostream>
#define GLEW_STATIC
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "headerfiles/Shader.h"

const unsigned int SCREEN_WIDTH = 480, SCREEN_HEIGHT = 360;

int main(){
	// initialize opengl
	glfwInit();
	// hint opengl version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // lock the window size, will disable the windows maximize button

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to creare window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// code here

	Shader ourShader("core.vert", "core.frag");

	// create triangle coordinate
	GLfloat vertices[] = {
		// position				// color (RGB)
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f, // bottom right
		 0.0f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f // middle top
	};

	// create Vertex Array & Vertex Buffer
	GLuint VAO, VBO;
	// gen vertex
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind vertex
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// get buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// pointing vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0); // enable the pointer

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1); // enable the pointer

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT);

		// render your code here

		ourShader.Use();
		glBindVertexArray(VAO); // bind vertex array
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0); // unbind vertex array

		// render code end

		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}