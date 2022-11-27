#version 330 core

out vec3 aColor;
out vec4 FragColor;
in vec2 atextCoord;

uniform sampler2D cubeTexture;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	float ambientStrenght = 0.1;
	vec3 ambient = lightColor *  ambientStrenght;
	vec3 result = objectColor * ambient;

	FragColor = texture(cubeTexture, atextCoord) * vec4(result, 1.0) ;
}