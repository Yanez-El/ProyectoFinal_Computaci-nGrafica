#version 330 core

layout (location = 0) in vec3 aPos; // Posición de los vértices
layout (location = 1) in vec2 aTexCoord; // Coordenadas de textura

out vec2 TexCoord;

uniform float uTime; // Tiempo uniforme para animar el agua
uniform float waveAmplitude = 0.05; // Amplitud de la onda
uniform float waveFrequency = 2.0; // Frecuencia de la onda
uniform float waveSpeed = 1.0; // Velocidad de la onda

void main()
{
    // Calcula el desplazamiento usando una onda sinusoidal
    float displacement = sin(aPos.x * waveFrequency + uTime * waveSpeed) * waveAmplitude;
    vec3 displacedPos = aPos;
    displacedPos.z += displacement; // Alteramos solo el eje Z para simular la onda
    
    gl_Position = vec4(displacedPos, 1.0);
    TexCoord = aTexCoord;
}
