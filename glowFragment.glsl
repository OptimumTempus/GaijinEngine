#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//Uniforms
uniform Material material;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;



void main()
{
	fs_color = vec4(lightColor.x,lightColor.y,lightColor.z , 1.0 );
}