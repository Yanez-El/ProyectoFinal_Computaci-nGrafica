#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include "Texture.h"

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
void Animation2();

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
float rotBrazoDN = 0.0f;
float rotBrazoIN = 0.0f;
float rotAntDJB = 0.0f;
float rotAntIJB = 0.0f; 
float rotPiernas = 0.0f;
float rotPiernaDJB = 0.0f;
float rotPiernaIJB = 0.0f;
float rotPieDJB = 0.0f;
float rotPieIJB = 0.0f;
float rotPiernaDN = 0.0f;
float rotPiernaIN = 0.0f;
float rotPieDN = 0.0f;
float rotPieIN = 0.0f;


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

GLfloat skyboxVertices[] = {
	// Positions
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};


GLuint indices[] =
{  // Note that we start from 0!
	0,1,2,3,
	4,5,6,7,
	8,9,10,11,
	12,13,14,15,
	16,17,18,19,
	20,21,22,23,
	24,25,26,27,
	28,29,30,31,
	32,33,34,35
};

//KeyFrames
float movJBX, movJBY;
float movNX, movNY;
float movBalonX, movBalonY;

#define MAX_FRAMES 20
int i_max_steps = 80;
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
	float rotPiernaDJB;
	float rotPieDJB;
	float rotPiernaIJB;
	float rotPieIJB;
	float incX;
	float incY;
	float incBalonX;
	float incBalonY;
	float incRotBrazoDJB;
	float incRotBrazoIJB;
	float incRotAntDJB;
	float incRotAntIJB;
	float incRotPiernaDJB;
	float incRotPieDJB;
	float incRotPiernaIJB;
	float incRotPieIJB;


}FRAME;


FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

FRAME KeyFrameN[MAX_FRAMES];
int FrameIndexN = 0;		//introducir datos
bool playN = false;
int playIndexN = 0;

void resetElements(FRAME KeyFrame[], int opcion)
{
	if (opcion == 1) {
		movJBX = KeyFrame[0].movJBX;
		movJBY = KeyFrame[0].movJBY;
		movBalonX = KeyFrame[0].movBalonX;
		movBalonY = KeyFrame[0].movBalonY;
		rotBrazoDJB = KeyFrame[0].rotBrazoDJB;
		rotBrazoIJB = KeyFrame[0].rotBrazoIJB;
		rotAntDJB = KeyFrame[0].rotAntDJB;
		rotAntIJB = KeyFrame[0].rotAntIJB;
		rotPiernaDJB = KeyFrame[0].rotPiernaDJB;
		rotPieDJB = KeyFrame[0].rotPieDJB;
		rotPiernaIJB = KeyFrame[0].rotPiernaIJB;
		rotPieIJB = KeyFrame[0].rotPieIJB;
	}
	else if (opcion == 2){
		movNX = KeyFrame[0].movJBX;
		movNY = KeyFrame[0].movJBY;
		rotBrazoDN = KeyFrame[0].rotBrazoDJB;
		rotBrazoIN = KeyFrame[0].rotBrazoIJB;
		rotPiernaDN = KeyFrame[0].rotPiernaDJB;
		rotPieDN = KeyFrame[0].rotPieDJB;
		rotPiernaIN = KeyFrame[0].rotPiernaIJB;
		rotPieIN = KeyFrame[0].rotPieIJB;
	}

}
void interpolation(FRAME KeyFrame[], int playIndex)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].movJBX - KeyFrame[playIndex].movJBX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].movJBY - KeyFrame[playIndex].movJBY) / i_max_steps;
	KeyFrame[playIndex].incBalonX = (KeyFrame[playIndex + 1].movBalonX - KeyFrame[playIndex].movBalonX) / i_max_steps;
	KeyFrame[playIndex].incBalonY = (KeyFrame[playIndex + 1].movBalonY - KeyFrame[playIndex].movBalonY) / i_max_steps;
	KeyFrame[playIndex].incRotBrazoDJB = (KeyFrame[playIndex + 1].rotBrazoDJB - KeyFrame[playIndex].rotBrazoDJB) / i_max_steps;
	KeyFrame[playIndex].incRotBrazoIJB = (KeyFrame[playIndex + 1].rotBrazoIJB - KeyFrame[playIndex].rotBrazoIJB) / i_max_steps;
	KeyFrame[playIndex].incRotAntDJB = (KeyFrame[playIndex + 1].rotAntDJB - KeyFrame[playIndex].rotAntDJB) / i_max_steps;
	KeyFrame[playIndex].incRotAntIJB = (KeyFrame[playIndex + 1].rotAntIJB - KeyFrame[playIndex].rotAntIJB) / i_max_steps;
	KeyFrame[playIndex].incRotPiernaDJB = (KeyFrame[playIndex + 1].rotPiernaDJB - KeyFrame[playIndex].rotPiernaDJB) / i_max_steps;
	KeyFrame[playIndex].incRotPieDJB = (KeyFrame[playIndex + 1].rotPieDJB - KeyFrame[playIndex].rotPieDJB) / i_max_steps;
	KeyFrame[playIndex].incRotPiernaIJB = (KeyFrame[playIndex + 1].rotPiernaIJB - KeyFrame[playIndex].rotPiernaIJB) / i_max_steps;
	KeyFrame[playIndex].incRotPieIJB = (KeyFrame[playIndex + 1].rotPieIJB - KeyFrame[playIndex].rotPieIJB) / i_max_steps;


}

void existeGuardado(void) {
	ifstream Guardado("animacion.txt");
	vector<float> datos;  // Arreglo donde guardarás los datos del archivo
	int j = 0;
	// Verificamos si el archivo existe
	if (!Guardado.is_open()) {
		// Si el archivo no existe, lo creamos y llenamos con datos
		cout << "El archivo no existe. Creando...\n";
		ofstream archivoEscritura("ejemplo.txt");
		archivoEscritura.close();
	}
	else {
		// Si el archivo existe, leemos los datos y los guardamos en el vector
		cout << "El archivo ya existe. Leyendo datos...\n";
		float numero;
		while (Guardado >> numero) {
			datos.push_back(numero);
		}
		Guardado.close();  // Cerramos el archivo después de leer
		// Mostramos los datos leídos
		cout << "Datos leidos correctamente\n";
		for (int i = 0; i < datos.size() / 12; i++) {
			KeyFrame[i].movJBX = datos[j];
			j++;
			KeyFrame[i].movJBY = datos[j];
			j++;
			KeyFrame[i].rotBrazoDJB = datos[j];
			j++;
			KeyFrame[i].rotBrazoIJB = datos[j];
			j++;
			KeyFrame[i].rotAntDJB = datos[j];
			j++;
			KeyFrame[i].rotAntIJB = datos[j];
			j++;
			KeyFrame[i].rotPiernaDJB = datos[j];
			j++;
			KeyFrame[i].rotPiernaIJB = datos[j];
			j++;
			KeyFrame[i].rotPieDJB = datos[j];
			j++;
			KeyFrame[i].rotPieIJB = datos[j];
			j++;
			KeyFrame[i].movBalonX = datos[j];
			j++;
			KeyFrame[i].movBalonY = datos[j];
			j++;
			
		}
		FrameIndex = (datos.size() / 12);
	}

	ifstream Guardado2("animacion2.txt");
	vector<float> datos2;  // Arreglo donde guardarás los datos del archivo
	j = 0;
	// Verificamos si el archivo existe
	if (!Guardado2.is_open()) {
		// Si el archivo no existe, lo creamos y llenamos con datos
		cout << "El archivo no existe. Creando...\n";
		ofstream archivoEscritura2("animacion2.txt");
		archivoEscritura2.close();
	}
	else {
		// Si el archivo existe, leemos los datos y los guardamos en el vector
		cout << "El archivo ya existe. Leyendo datos...\n";
		float numero2;
		while (Guardado2 >> numero2) {
			datos2.push_back(numero2);
		}
		Guardado2.close();  // Cerramos el archivo después de leer
		// Mostramos los datos leídos
		cout << "Datos leidos correctamente\n";
		for (int i = 0; i < datos2.size() / 8; i++) {
			KeyFrameN[i].movJBX = datos2[j];
			j++;
			KeyFrameN[i].movJBY = datos2[j];
			j++;
			KeyFrameN[i].rotBrazoDJB = datos2[j];
			j++;
			KeyFrameN[i].rotBrazoIJB = datos2[j];
			j++;
			KeyFrameN[i].rotPiernaDJB = datos2[j];
			j++;
			KeyFrameN[i].rotPiernaIJB = datos2[j];
			j++;
			KeyFrameN[i].rotPieDJB = datos2[j];
			j++;
			KeyFrameN[i].rotPieIJB = datos2[j];
			j++;

		}
		FrameIndexN = (datos2.size() / 8);
	}
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
	Shader SkyBoxShader("Shader/SkyBox.vs", "Shader/SkyBox.frag");

	
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
	Model Mustango((char*)"Models/Models/Mustang/Mustango.obj");
	Model Tesla((char*)"Models/Models/Tesla/Tesla.obj");
	Model RejaFut((char*)"Models/Models/RejaCanchaF/rejaFut.obj");
	Model RejaBask((char*)"Models/Models/rejaBask/rejaBask.obj");
	Model Casita((char*)"Models/Models/Casita/juegos.obj");


	Model cuerpo_hotel((char*)"Models/Models/cuerpo_hotel/cuerpo_casa.obj");
	Model paredes_escaleras_pisos((char*)"Models/Models/paredes_escaleras_pisos/paredes_escaleras_pisos.obj");
	Model muebles_baja((char*)"Models/Models/muebles_baja/muebles_baja.obj");
	Model muebles_alta((char*)"Models/Models/muebles_alta/muebles_alta.obj");
	Model muebles_techo((char*)"Models/Models/muebles_techo/muebles_techo.obj");
	Model BalonB((char*)"Models/Models/PisoBasket/BasketBall.obj");
	Model CuerpoNino((char*)"Models/Models/nino/CuerpoN.obj");
	Model BrazoDN((char*)"Models/Models/nino/BrazoDN.obj");
	Model BrazoIN((char*)"Models/Models/nino/BrazoIN.obj");
	Model PiernaDN((char*)"Models/Models/nino/PiernaDN.obj");
	Model PiernaIN((char*)"Models/Models/nino/PiernaIN.obj");
	Model PieDN((char*)"Models/Models/nino/PieDN.obj");
	Model PieIN((char*)"Models/Models/nino/PieIN.obj");

	//Contenedor
	Model contenedor((char*)"Models/Models/contenedor/contenedores.obj");
	Model pisos_hotel((char*)"Models/Models/pisos_hotel/pisos_hotel.obj");
	Model cuartos_hotel((char*)"Models/Models/cuartos_hotel/cuartos_hotel.obj");
	Model muebles_contenedores((char*)"Models/Models/muebles_contenedores/muebles_contenedores.obj");
	Model techos((char*)"Models/Models/Techos/techos.obj");
	Model techoCentral((char*)"Models/Models/techo_central/techo_central.obj");
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
		KeyFrame[i].rotAntIJB = 0;
		KeyFrame[i].rotPiernaDJB = 0;
		KeyFrame[i].rotPieDJB = 0;
		KeyFrame[i].rotPiernaIJB = 0;
		KeyFrame[i].rotPieIJB = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incBalonX = 0;
		KeyFrame[i].incBalonY = 0;
		KeyFrame[i].incRotBrazoDJB = 0;
		KeyFrame[i].incRotBrazoIJB = 0;
		KeyFrame[i].incRotAntDJB = 0;
		KeyFrame[i].incRotAntIJB = 0;
		KeyFrame[i].incRotPiernaDJB = 0;
		KeyFrame[i].incRotPieDJB = 0;
		KeyFrame[i].incRotPiernaIJB = 0;
		KeyFrame[i].incRotPieIJB = 0;
		KeyFrameN[i].movJBX = 0;
		KeyFrameN[i].movJBY = 0;
		KeyFrameN[i].movBalonX = 0;
		KeyFrameN[i].movBalonY = 0;
		KeyFrameN[i].rotBrazoDJB = 0;
		KeyFrameN[i].rotBrazoIJB = 0;
		KeyFrameN[i].rotAntDJB = 0;
		KeyFrameN[i].rotAntIJB = 0;
		KeyFrameN[i].rotPiernaDJB = 0;
		KeyFrameN[i].rotPieDJB = 0;
		KeyFrameN[i].rotPiernaIJB = 0;
		KeyFrameN[i].rotPieIJB = 0;
		KeyFrameN[i].incX = 0;
		KeyFrameN[i].incY = 0;
		KeyFrameN[i].incBalonX = 0;
		KeyFrameN[i].incBalonY = 0;
		KeyFrameN[i].incRotBrazoDJB = 0;
		KeyFrameN[i].incRotBrazoIJB = 0;
		KeyFrameN[i].incRotAntDJB = 0;
		KeyFrameN[i].incRotAntIJB = 0;
		KeyFrameN[i].incRotPiernaDJB = 0;
		KeyFrameN[i].incRotPieDJB = 0;
		KeyFrameN[i].incRotPiernaIJB = 0;
		KeyFrameN[i].incRotPieIJB = 0;

	}

	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

	//Skybox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/negx.jpg");
	faces.push_back("SkyBox/posx.jpg");
	faces.push_back("SkyBox/posy.jpg");
	faces.push_back("SkyBox/negy.jpg");
	faces.push_back("SkyBox/posz.jpg");
	faces.push_back("SkyBox/negz.jpg");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 200.0f);

	existeGuardado();

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
		Animation2();

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
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);



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
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
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
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp


		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);
		PisoBask.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		Canastas.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		model = glm::translate(model, glm::vec3(movBalonX, movBalonY, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BalonB.Draw(lightingShader);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		PisoFut.Draw(lightingShader);
		Porterias.Draw(lightingShader);
		Estacionamientos.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Mustango.Draw(lightingShader);
		Tesla.Draw(lightingShader);


		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		Dog.Draw(lightingShader);
		RejaFut.Draw(lightingShader);
		RejaBask.Draw(lightingShader);
		techos.Draw(lightingShader);
		cuerpo_hotel.Draw(lightingShader);
		paredes_escaleras_pisos.Draw(lightingShader);
		muebles_baja.Draw(lightingShader);
		muebles_alta.Draw(lightingShader);
		muebles_techo.Draw(lightingShader);
		contenedor.Draw(lightingShader);
		muebles_contenedores.Draw(lightingShader);
		techoCentral.Draw(lightingShader);
		sillones.Draw(lightingShader);
		mesas_pasillo.Draw(lightingShader);
		Alberca.Draw(lightingShader);
		Casita.Draw(lightingShader);

		//Modelo del niño
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		modelTemp = model = glm::translate(model, glm::vec3(-7.24f, 1.44f, -4.991f));
		modelTemp = model = glm::translate(model, glm::vec3(0.0f, movNX, movNY));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoNino.Draw(lightingShader);
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.192f, 0.159f, 0.0f));
		model = glm::rotate(model, glm::radians(rotBrazoDN), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDN.Draw(lightingShader);
		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.188f, 0.205f, 0.0f));
		model = glm::rotate(model, glm::radians(rotBrazoIN), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIN.Draw(lightingShader);

		model = modelTemp;
		modelTemp2 = model = glm::translate(model, glm::vec3(0.109f, -0.51f, 0.0f));
		modelTemp2 = model = glm::rotate(model, glm::radians(rotPiernaDN), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDN.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(-0.015f, -0.43f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPieDN), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieDN.Draw(lightingShader);

		model = modelTemp;
		modelTemp2 = model = glm::translate(model, glm::vec3(-0.136f, -0.51f, 0.0f));
		modelTemp2 = model = glm::rotate(model, glm::radians(rotPiernaIN), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIN.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(0.032f, -0.43f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPieIN), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieIN.Draw(lightingShader);


		//Dibujo de la nadadora
		model = glm::mat4(1);
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
		modelTemp2 = model = glm::rotate(model, glm::radians(rotPiernaDJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDJB.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(-0.028f, -0.385f, -0.082f));
		model = glm::rotate(model, glm::radians(rotPieDJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieDJB.Draw(lightingShader);

		model = modelTemp;
		modelTemp2 = model = glm::translate(model, glm::vec3(0.112f, -0.381f, 0.035f));
		modelTemp2 = model = glm::rotate(model, glm::radians(rotPiernaIJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIJB.Draw(lightingShader);
		model = modelTemp2;
		model = glm::translate(model, glm::vec3(-0.027f, -0.384f, 0.121f));
		model = glm::rotate(model, glm::radians(rotPieIJB), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PieIJB.Draw(lightingShader);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
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
		glBindVertexArray(0);

		//Draw Skybox
		glDepthFunc(GL_LEQUAL);
		SkyBoxShader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);

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
		camera.ProcessKeyboard(FORWARD, deltaTime * 3);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime * 3);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime * 3);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime * 3);


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
			}
			else if (rotCuerpo > 360.0f) {
				rotCuerpo = 0.0f;
				rotCuerpoX = 0.0f;
				sentidoBrazos = 1.0f;
			}
			else if (movNado.x > -18.0f && movNado.x < -15.0f) {
				movNado.z -= 0.01f;
				rotCuerpo += 0.3f;
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
			}
			else if (movNado.x > -2.0f && movNado.x < 1.0f) {
				movNado.z += 0.01f;
				rotCuerpo += 0.3f;
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
			resetElements(KeyFrame, 1);
			//First Interpolation				
			interpolation(KeyFrame, playIndex);

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

		

	}

	if (keys[GLFW_KEY_N])
	{
		if (playN == false && (FrameIndexN > 1))
		{
			/*llenado(FrameIndexN);*/
			resetElements(KeyFrameN, 2);
			//First Interpolation				
			interpolation(KeyFrameN, playIndexN);

			playN = true;
			playIndexN = 0;
			i_curr_steps = 0;
		}
		else
		{
			playN = false;
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
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation(KeyFrame, playIndex);
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
			rotPiernaDJB += KeyFrame[playIndex].incRotPiernaDJB;
			rotPieDJB += KeyFrame[playIndex].incRotPieDJB;
			rotPiernaIJB += KeyFrame[playIndex].incRotPiernaIJB;
			rotPieIJB += KeyFrame[playIndex].incRotPieIJB;


			i_curr_steps++;
		}

	}
}

void Animation2() {

	if (playN)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndexN++;
			if (playIndexN > FrameIndexN - 2)	//end of total animation?
			{
				playIndexN = 0;
				playN = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation(KeyFrameN, playIndexN);
			}
		}
		else
		{
			//Draw animation
			movNX += KeyFrameN[playIndexN].incX;
			movNY += KeyFrameN[playIndexN].incY;
			rotBrazoDN += KeyFrameN[playIndexN].incRotBrazoDJB;
			rotBrazoIN += KeyFrameN[playIndexN].incRotBrazoIJB;
			rotPiernaDN += KeyFrameN[playIndexN].incRotPiernaDJB;
			rotPieDN += KeyFrameN[playIndexN].incRotPieDJB;
			rotPiernaIN += KeyFrameN[playIndexN].incRotPiernaIJB;
			rotPieIN += KeyFrameN[playIndexN].incRotPieIJB;


			i_curr_steps++;
		}

	}
}