#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D waterTexture; // Textura de agua

void main()
{
    // Muestra la textura de agua en el plano
    FragColor = texture(waterTexture, TexCoord);
}
