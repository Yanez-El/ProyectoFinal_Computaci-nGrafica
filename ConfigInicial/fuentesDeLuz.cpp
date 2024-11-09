#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"
#include <iostream>
#include <cmath>

#include <assimp/Importer.hpp> 
#include <assimp/scene.h> 
#include <assimp/postprocess.h>
#include <vector>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include <functional>

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animaNado();
void Animation();

// Window dimensions
const GLuint WIDTH = 1280, HEIGHT = 720;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 15.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;
bool delante = true;
bool atras = false;
bool giroDerecha = false;
bool step = false;
int nado = 0;

//Variables de movimiento
glm::vec3 movNado(0.0f);
float sentidoBrazos = 1.0f;
float rotCuerpo = 0.0f;
float rotCuerpoX = 0.0f;
float rotBrazos = 0.0f;
float rotBrazoDJB = 0.0f;
float rotBrazoIJB = 0.0f;
float rotAntDJB = 0.0f;
float rotAntIJB = 0.0f;
float rotPiernas = 0.0f;
float rotPiernaDJB = 0.0f;
float rotPiernaIJB = 0.0f;
float rotPieDJB = 0.0f;
float rotPieIJB = 0.0f;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

//KeyFrames
float movJBX, movJBY;
float movBalonX, movBalonY;

#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame {

	float movJBX;
	float movJBY;
	float movBalonX;
	float movBalonY;
	float rotBrazoDJB;
	float rotBrazoIJB;
	float rotAntDJB;
	float rotAntIJB;
	float incX;
	float incY;
	float incBalonX;
	float incBalonY;
	float incRotBrazoDJB;
	float incRotBrazoIJB;
	float incRotAntDJB;
	float incRotAntIJB;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].movJBX = movJBX;
	KeyFrame[FrameIndex].movJBY = movJBY;
	KeyFrame[FrameIndex].movBalonX = movBalonX;
	KeyFrame[FrameIndex].movBalonY = movBalonY;
	KeyFrame[FrameIndex].rotBrazoDJB = rotBrazoDJB;
	KeyFrame[FrameIndex].rotAntDJB = rotAntDJB;
	KeyFrame[FrameIndex].rotBrazoIJB = rotBrazoIJB;
	KeyFrame[FrameIndex].rotAntIJB = rotAntIJB;


	FrameIndex++;
}

void resetElements(void)
{
	movJBX = KeyFrame[0].movJBX;
	movJBY = KeyFrame[0].movJBY;
	movBalonX = KeyFrame[0].movBalonX;
	movBalonY = KeyFrame[0].movBalonY;
	rotBrazoDJB = KeyFrame[0].rotBrazoDJB;
	rotBrazoIJB = KeyFrame[0].rotBrazoIJB;
	rotAntDJB = KeyFrame[0].rotAntDJB;
	rotAntIJB = KeyFrame[0].rotAntIJB;

}
void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].movJBX - KeyFrame[playIndex].movJBX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].movJBY - KeyFrame[playIndex].movJBY) / i_max_steps;
	KeyFrame[playIndex].incBalonX = (KeyFrame[playIndex + 1].movBalonX - KeyFrame[playIndex].movBalonX) / i_max_steps;
	KeyFrame[playIndex].incBalonY = (KeyFrame[playIndex + 1].movBalonY - KeyFrame[playIndex].movBalonY) / i_max_steps;
	KeyFrame[playIndex].incRotBrazoDJB = (KeyFrame[playIndex + 1].rotBrazoDJB - KeyFrame[playIndex].rotBrazoDJB) / i_max_steps;
	KeyFrame[playIndex].incRotBrazoIJB = (KeyFrame[playIndex + 1].rotBrazoIJB - KeyFrame[playIndex].rotBrazoIJB) / i_max_steps;
	KeyFrame[playIndex].incRotAntDJB = (KeyFrame[playIndex + 1].rotAntDJB - KeyFrame[playIndex].rotAntDJB) / i_max_steps;
	KeyFrame[playIndex].incRotAntIJB = (KeyFrame[playIndex + 1].rotAntIJB - KeyFrame[playIndex].rotAntIJB) / i_max_steps;
	

}



glm::vec3 Light1 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Estructuras de datos para almacenar los vértices, texturas, etc.
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final CGIH6 Equipo 5", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	Shader aguaShader("Shader/animAgua.vs", "Shader/animAgua.frag");
	
	Model Dog((char*)"Models/Models/Barda/Barda.obj");
	Model Piso((char*)"Models/Models/Piso/Piso.obj");
	Model PisoFut((char*)"Models/Models/PisoFutbol/pisoFut.obj");
	Model Porterias((char*)"Models/Models/PisoFutbol/Porterias.obj");
	Model PisoBask((char*)"Models/Models/PisoBasket/pisoBask.obj");
	Model Canastas((char*)"Models/Models/PisoBasket/canastas.obj");
	Model Alberca((char*)"Models/Models/AlberK/Alberca.obj");
	Model AguAlberca((char*)"Models/Models/AlberK/Agua.obj");
	Model NadadoraBody((char*)"Models/Models/Nadadora/NadadoraB.obj");
	Model NadadoraBrazos((char*)"Models/Models/Nadadora/BrazosNadadora.obj");
	Model NadadoraPD((char*)"Models/Models/Nadadora/PiernaD.obj");
	Model NadadoraPI((char*)"Models/Models/Nadadora/PiernaI.obj");
	Model CuerpoJB((char*)"Models/Models/jugadorBasket/CuerpoJB.obj");
	Model BrazoDJB((char*)"Models/Models/jugadorBasket/BrazoDJB.obj");
	Model BrazoIJB((char*)"Models/Models/jugadorBasket/BrazoIJB.obj");
	Model AntebrazoDJB((char*)"Models/Models/jugadorBasket/AntebrazoDJB.obj");
	Model AntebrazoIJB((char*)"Models/Models/jugadorBasket/AntebrazoIJB.obj");
	Model PiernaDJB((char*)"Models/Models/jugadorBasket/PiernaDJB.obj");
	Model PiernaIJB((char*)"Models/Models/jugadorBasket/PiernaIJB.obj");
	Model PieDJB((char*)"Models/Models/jugadorBasket/PieDJB.obj");
	Model PieIJB((char*)"Models/Models/jugadorBasket/PieIJB.obj");

	Model Estacionamientos((char*)"Models/Models/Estacionamientos/estacionamientos.obj");
	Model RejaFut((char*)"Models/Models/RejaCanchaF/rejaFut.obj");
	Model RejaBask((char*)"Models/Models/rejaBask/rejaBask.obj");
	Model BalonB((char*)"Models/Models/PisoBasket/BasketBall.obj");
	Model Tsuru((char*)"Models/Models/Tsuru/Tsuru.obj");
	Model Casita((char*)"Models/Models/Juegos/juegos.obj");

	//Contenedor
	Model contenedor((char*)"Models/Models/contenedor/contenedores.obj");
	//Model hotel_amueblado((char*)"Models/Models/hotel/hotel_amueblado.obj");

	Model techos((char*)"Models/Models/Techos/techos.obj");
	//Model techoCentral((char*)"Models/Models/techo_central/techo_central.obj");
	Model acapulco((char*)"Models/Models/acapulco/acapulco.obj");
	Model sillones((char*)"Models/Models/sillones/sillones.obj");
	Model mesas_pasillo((char*)"Models/Models/mesas/mesas_pasillo.obj");

	//KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].movJBX = 0;
		KeyFrame[i].movJBY = 0;
		KeyFrame[i].movBalonX = 0;
		KeyFrame[i].movBalonY = 0;
		KeyFrame[i].rotBrazoDJB = 0;
		KeyFrame[i].rotBrazoIJB = 0;
		KeyFrame[i].rotAntDJB = 0;
		KeyFrame[i].rotAntDJB = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incBalonX = 0;
		KeyFrame[i].incBalonY = 0;
		KeyFrame[i].incRotBrazoDJB = 0;
		KeyFrame[i].incRotBrazoIJB = 0;
		KeyFrame[i].incRotAntDJB = 0;
		KeyFrame[i].incRotAntIJB = 0;

	}



	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 200.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		//Load Model
		animaNado();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		
		

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

                  glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.6f,0.6f,0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.3f, 0.3f, 0.3f);


		// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= sin(glfwGetTime() *Light1.z);

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.075f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.0f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.0f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"),0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp2
	

		//Carga de modelo 
        view = camera.GetViewMatrix();	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);
		PisoBask.Draw(lightingShader);
		Canastas.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		modelTemp = model = glm::translate(model, glm::vec3(movBalonX, movBalonY, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BalonB.Draw(lightingShader);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);

		PisoFut.Draw(lightingShader);
		Porterias.Draw(lightingShader);
		Estacionamientos.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);

	    Dog.Draw(lightingShader);
	    RejaFut.Draw(lightingShader);
	    RejaBask.Draw(lightingShader);
		techos.Draw(lightingShader);
	    Tsuru.Draw(lightingShader);
		//hotel_amueblado.Draw(lightingShader);
		contenedor.Draw(lightingShader);
		techos.Draw(lightingShader);
		//techoCentral.Draw(lightingShader);
		acapulco.Draw(lightingShader);
		sillones.Draw(lightingShader);
		mesas_pasillo.Draw(lightingShader);
		Alberca.Draw(lightingShader);
		Casita.Draw(lightingShader);


		//Dibujo de la nadadora
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		modelTemp = model = glm::translate(model, glm::vec3(-42.976f, -0.427f, 25.693f));
		modelTemp = model = glm::translate(model, glm::vec3(movNado));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(0.0f, -1.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpoX), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		NadadoraBody.Draw(lightingShader);
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.166f, 0.027f, 0.0f));
		model = glm::rotate(model, glm::radians(rotBrazos), glm::vec3(0.0f, 0.0f, sentidoBrazos));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		NadadoraBrazos.Draw(lightingShader);
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.539f, 0.059f, 0.077f));
		model = glm::rotate(model, glm::radians(rotPiernas), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		NadadoraPD.Draw(lightingShader);
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.5f, 0.057f, -0.061f));
		model = glm::rotate(model, glm::radians(rotPiernas), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		NadadoraPI.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0f);
		//Dibujo del jugador de basket
		model = glm::mat4(1);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		modelTemp = model = glm::translate(model, glm::vec3(-51.384f, 1.307f, 40.716f));
		modelTemp = model = glm::translate(model, glm::vec3(movJBX, movJBY, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoJB.Draw(lightingShader);
		model = modelTemp;
		modelTemp2 = model = glm::translate(model, glm::vec3(0.028f, 0.181f, -0.196f));
		modelTemp2 = model = glm::rotate(model, glm::radians(rotBrazoDJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDJB.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(0.091f, -0.219f, -0.191f));
		model = glm::rotate(model, glm::radians(rotAntDJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		AntebrazoDJB.Draw(lightingShader);
		model = modelTemp;
		modelTemp2 = model = glm::translate(model, glm::vec3(0.028f, 0.180f, 0.189f));
		modelTemp2 = model = glm::rotate(model, glm::radians(rotBrazoIJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIJB.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(0.091f, -0.219f, 0.167f));
		model = glm::rotate(model, glm::radians(rotAntIJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		AntebrazoIJB.Draw(lightingShader);

		model = modelTemp;
		modelTemp2 = model = glm::translate(model, glm::vec3(0.112f, -0.380f, -0.085f));
		/*modelTemp = model = glm::translate(model, glm::vec3(movNado));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(0.0f, -1.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpoX), glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDJB.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(-0.028f, -0.385f, -0.082f));
		/*modelTemp = model = glm::translate(model, glm::vec3(movNado));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(0.0f, -1.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpoX), glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieDJB.Draw(lightingShader);

		model = modelTemp;
		modelTemp2 = model = glm::translate(model, glm::vec3(0.112f, -0.381f, 0.035f));
		/*modelTemp = model = glm::translate(model, glm::vec3(movNado));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(0.0f, -1.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpoX), glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIJB.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(-0.027f, -0.384f, 0.121f));
		/*modelTemp = model = glm::translate(model, glm::vec3(movNado));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(0.0f, -1.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(rotCuerpoX), glm::vec3(1.0f, 0.0f, 0.0f));*/
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieIJB.Draw(lightingShader);

		glBindVertexArray(0);

		// Activar el shader
		aguaShader.Use();
		glUniform1f(glGetUniformLocation(aguaShader.Program, "time"), currentFrame);
		modelLoc = glGetUniformLocation(aguaShader.Program, "model");
		viewLoc = glGetUniformLocation(aguaShader.Program, "view");
		projLoc = glGetUniformLocation(aguaShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.75f);
		AguAlberca.Draw(aguaShader);
		glDisable(GL_BLEND); //Desactiva el canal alfa
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime * 2);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime * 2);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime * 2);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime * 2);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}
	if (keys[GLFW_KEY_M])
	{
		movJBX += 0.02f;
	}
	if (keys[GLFW_KEY_N])
	{
		movJBX -= 0.02f;
	}
	if (keys[GLFW_KEY_B])
	{
		movJBY += 0.02f;
	}
	if (keys[GLFW_KEY_V])
	{
		movJBY -= 0.02f;
	}
	if (keys[GLFW_KEY_1])
	{
		rotBrazoDJB += 0.2f;
	}
	if (keys[GLFW_KEY_2])
	{
		rotBrazoDJB -= 0.2f;
	}
	if (keys[GLFW_KEY_3])
	{
		rotBrazoIJB += 0.2f;
	}
	if (keys[GLFW_KEY_4])
	{
		rotBrazoIJB -= 0.2f;
	}
	if (keys[GLFW_KEY_5])
	{
		rotAntDJB += 0.2f;
	}
	if (keys[GLFW_KEY_6])
	{
		rotAntDJB -= 0.2f;
	}
	if (keys[GLFW_KEY_7])
	{
		rotAntIJB += 0.2f;
	}
	if (keys[GLFW_KEY_8])
	{
		rotAntIJB -= 0.2f;
	}
	if (keys[GLFW_KEY_9])
	{
		movBalonX += 0.02f;
	}
	if (keys[GLFW_KEY_0])
	{
		movBalonX -= 0.02f;
	}
	if (keys[GLFW_KEY_O])
	{
		movBalonY += 0.02f;
	}
	if (keys[GLFW_KEY_P])
	{
		movBalonY -= 0.02f;
	}
}

void animaNado() {
	if (nado == 1) {
		if (delante) {
			movNado.x -= 0.01f;
			if (rotCuerpo > 270.0f && rotCuerpo < 360.0f) {
				movNado.z += 0.01f;
				rotCuerpo += 0.3f;
				rotCuerpoX += 0.6f;
				printf("%.3f\n", rotCuerpo);
			}
			else if (rotCuerpo > 360.0f) {
				rotCuerpo = 0.0f;
				rotCuerpoX = 0.0f;
				sentidoBrazos = 1.0f;
			}
			else if (movNado.x > -18.0f && movNado.x < -15.0f) {
				movNado.z -= 0.01f;
				rotCuerpo += 0.3f;
				printf("%.3f\n", rotCuerpo);
			}
			else if (movNado.x < -18.0f) {
				delante = false;
				atras = true;
			}
		}
		else if (atras) {
			movNado.x += 0.01;
			if (movNado.x > -18.0f && movNado.x < -15.0f) {
				movNado.z -= 0.01f;
				rotCuerpo += 0.3f;
				rotCuerpoX += 0.6f;
				printf("%.3f\n", rotCuerpo);
			}
			else if (movNado.x > -2.0f && movNado.x < 1.0f) {
				movNado.z += 0.01f;
				rotCuerpo += 0.3f;
				printf("%.3f\n", rotCuerpo);
			}
			else if (movNado.x > 1.0f) {
				delante = true;
				atras = false;
			}

			if (movNado.x > -15.0f) {
				sentidoBrazos = -1.0f;
			}
		}
		rotBrazos += 3.0f;

		if (!step) {
			rotPiernas += 1.0f;
			if (rotPiernas > 15.0f) {
				step = true;
			}
		}
		else {
			rotPiernas -= 1.0f;
			if (rotPiernas < -15.0f) {
				step = false;
			}
		}

	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{

	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (keys[GLFW_KEY_K])
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

	}

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_F])
	{
		if (nado == 0) {
			nado = 1;
		}
		else {
			nado = 0;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		
		//	active = !active;
		//	if (active)
		//	{
		//		Light1 = glm::vec3(1.0f, 1.0f, 0.0f);
		//	}
		//	else
		//	{
		//		Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		//	}
		//}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void Animation() {

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			movJBX += KeyFrame[playIndex].incX;
			movJBY += KeyFrame[playIndex].incY;
			movBalonX += KeyFrame[playIndex].incBalonX;
			movBalonY += KeyFrame[playIndex].incBalonY;
			rotBrazoDJB += KeyFrame[playIndex].incRotBrazoDJB;
			rotBrazoIJB += KeyFrame[playIndex].incRotBrazoIJB;
			rotAntDJB += KeyFrame[playIndex].incRotAntDJB;
			rotAntIJB += KeyFrame[playIndex].incRotAntIJB;


			i_curr_steps++;
		}

	}

}