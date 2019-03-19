#version 440

struct Material
{
	float attenuation;
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


	//Functions
vec3 calculateAmbient(Material material, vec3 lightColor)
{

	return (material.ambient * lightColor);
};

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_noraml, vec3 lightPos, vec3 lightColor)
{
	vec3 posToLightDirVec = normalize(lightPos - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = (material.diffuse * lightColor) * diffuse;

	return diffuseFinal;
};



vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos, vec3 cameraPos, vec3 lightColor)
{
	vec3 lightToPosDirVec = normalize(vs_position - lightPos);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 35);
	vec3 specularFinal = (material.specular * lightColor) * specularConstant * texture(material.specularTex, vs_texcoord).rgb;

	return specularFinal;
};

float calculateAttenuation(Material material, vec3 lightPos, vec3 vs_position)
{
	float distanceToLight = length(lightPos - vs_position);
	float att = 1.0 / (1.0 + .2 * pow(distanceToLight, 2));
	return att;
};


void main()
{
		//Ambient Light
	vec3 ambientFinal  = calculateAmbient(material, lightColor);

		//Diffuse Light
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos, lightColor);

		//Specular Light
	vec3 specularFinal = calculateSpecular(material,vs_position,vs_normal,lightPos,cameraPos, lightColor);
	

		//Attenuation
	float att = calculateAttenuation(material, lightPos, vs_position);

	vec4 gamma = vec4(1.0/2.2,1.0/2.2,1.0/2.2,1.0/2.2);

	fs_color = texture(material.diffuseTex, vs_texcoord) * (vec4(ambientFinal, 1.f) + att*( vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f)) );

}