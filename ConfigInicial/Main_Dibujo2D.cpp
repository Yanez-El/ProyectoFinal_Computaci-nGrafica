/*
	Práctica 1 Dibujo de primitivas 2D
	Fernando Yañez García
	17 de agosto de 2024
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D Fernando", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		0.41f, 0.30f, 0.0f,    0.4471f,0.7451f,0.5961f,  // top right
		0.47f, 0.36f, 0.0f,    0.4471f,0.7451f,0.5961f,  // bottom right
		0.51f, 0.49f, 0.0f,   0.4471f,0.7451f,0.5961f,  // bottom left
		0.40f, 0.58f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		0.27f, 0.50f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		0.24f, 0.415f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		
		0.30f, 0.38f, 0.0f,   0.4f,0.7f,0.5f,  // top right
		0.07f, 0.53f, 0.0f,   0.4f,0.7f,0.5f,  // top right
		-0.11f, 0.46f, 0.0f,   0.4f,0.7f,0.5f,  // bottom right
		-0.25f, 0.18f, 0.0f,  0.4f,0.7f,0.5f,  // bottom left
		-0.23f, -0.18f, 0.0f,  0.4f,0.7f,0.5f, // top left 
		0.19f, -0.13f, 0.0f,  0.4f,0.7f,0.5f, // top left 
		0.45f, 0.04f, 0.0f,  0.4f,0.7f,0.5f, // top left 
		0.51f, 0.23f, 0.0f,  0.4f,0.7f,0.5f, // top left 
		
		0.07f, 0.53f, 0.0f,   0.4f,0.7f,0.5f,  // bottom left
		-0.22f, 0.52f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		-0.5f, 0.4f, 0.0f,   0.4f,0.7f,0.5f, // top left 

		-0.50f, 0.40f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		-0.15f, 0.37f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		-0.1f, 0.45f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		0.07f, 0.53f, 0.0f,   0.4471f,0.7451f,0.5961f,  // bottom left 

		0.51f, 0.23f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		0.66f, -0.07f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		0.54f, -0.36f, 0.0f,   0.4f,0.7f,0.5f, // top left 

		0.54f, -0.36f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		0.39f, 0.00f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		0.45f, 0.04f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		0.51f, 0.23f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		
		-0.23f, -0.04f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		-0.38f, -0.08f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		-0.63f, -0.03f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		-0.24f, 0.02f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		
		-0.24f, 0.02f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		-0.63f, -0.03f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		-0.37f, 0.03f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		-0.2425f, 0.04f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		
		0.06f, -0.60f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		0.01f, -0.15125f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		0.06f, -0.145f, 0.0f,   0.4f,0.7f,0.5f, // top left 
		0.11f, -0.33f, 0.0f,   0.4f,0.7f,0.5f, // top left 

		0.06f, -0.60f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		0.01f, -0.15125f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		-0.06f, -0.16f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 
		-0.1f, -0.31f, 0.0f,   0.4471f,0.7451f,0.5961f, // top left 

	};
	unsigned int indices[] = {  // note that we start from 0!
		0,2,5,// second Triangle
		2,3,6,
		
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


       /* glPointSize(10);
        glDrawArrays(GL_POINTS,0,1);*/
        
        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,4);
        
        glDrawArrays(GL_POLYGON,0,6);
        glDrawArrays(GL_POLYGON,6,8);
        glDrawArrays(GL_TRIANGLES,14,3);
        glDrawArrays(GL_POLYGON,17,4);
		glDrawArrays(GL_TRIANGLES, 21, 3);
		glDrawArrays(GL_POLYGON, 24, 4);
		glDrawArrays(GL_POLYGON, 28, 4);
		glDrawArrays(GL_POLYGON, 32, 4);
		glDrawArrays(GL_POLYGON, 36, 4);
		glDrawArrays(GL_POLYGON, 40, 4);
        //glDrawElements(GL_TRIANGLES, 5,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}