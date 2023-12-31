#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shaders.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("3.3.shader.vs", "3.3.shader.fs");

	//Exercise 1 vertices
	float vertices[] =
	{
		//positions		//colors		//texture coords
		 0.2f,  0.2f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, //top right
		 0.2f, -0.2f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, //bottom right
		-0.2f, -0.2f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, //bottom left
		-0.2f,  0.2f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f  //top left
	};

	float dragon[] =
	{	//positions			//colors
		 0.0f,    0.25f,  0.0f, 	1.0f, 0.0f, 0.0f,
		-0.25f,   0.0f,   0.0f, 	1.0f, 0.0f, 0.0f,
		-0.25f,  -0.125f, 0.0f, 	1.0f, 0.0f, 0.0f,
		-0.5f,   -0.25f,  0.0f, 	0.0f, 1.0f, 1.0f,
		-0.25f,  -0.25f,  0.0f, 	0.0f, 1.0f, 0.0f,
		-0.25f,  -0.375f, 0.0f, 	1.0f, 1.0f, 0.0f,
		-0.125f, -0.375f, 0.0f, 	0.0f, 0.5f, 0.0f,
		 0.0f,    0.0f,   0.0f, 	0.4f, 0.2f, 0.1f,
		 0.25f,   0.0f,   0.0f, 	1.0f, 0.5f, 0.0f
	};

	// texture coordinates
	unsigned int indices[] =
	{
		0, 1, 3, //first triangle
		1, 2, 3 //second triangle
	};

	float dIndices[] =
	{
		0, 1, 8, //first tri
		1, 4, 7, //second tri
		2, 3, 4, //third tri
		4, 5, 6 //fourth tri
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(dragon), dragon, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(dIndices), dIndices, GL_STATIC_DRAW);
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Texture Coords
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//loading texture
	//unsigned int texture1;
	//glGenTextures(1, &texture1);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//set texture wrapping perameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//set texture filtering perameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//int width, height, nrChannels;

	//unsigned char *data = stbi_load("cobblestone.png", &width, &height, &nrChannels, 0);
	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	//stbi_image_free(data);

	//ourShader.setInt("texture1", 0);

	//render loop
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		//bind texture
	//	glBindTexture(GL_TEXTURE_2D, texture1);

		//draw triangles
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	
	return 0;
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
