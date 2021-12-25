#version 430

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  sampler2D diffuseTex;
  sampler2D specularTex;
};

struct Light {
  vec3 position;
  vec3 color;
  vec3 ambient;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;


// Uniforms
uniform Material material;
uniform Light light;
//uniform vec3 lightPos0;
uniform vec3 cameraPos;

// Functions
vec3 calcAmbient(Material material){
  return material.ambient * light.ambient;
}

vec3 calcDiffuse(Material material, vec3 position, vec3 normal, vec3 lightPos){
  vec3 posToLightDirVec = normalize(lightPos - position);
  float diffuse = clamp(dot(posToLightDirVec, normal), 0, 1);
  return  material.diffuse * diffuse;
}

vec3 calcSpecular(Material material, vec3 position, vec3 normal, vec3 lightPos, vec3 cameraPos){
  vec3 lightToPosDirVec = normalize(position - lightPos);
  vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(normal)));
  vec3 posToViewDirVec = normalize(cameraPos - position);
  float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 50);
  return material.specular * specularConstant; //* texture(material.specularTex, vs_texcoord).rgb;
}

void main() {
  //fs_color = vec4(vs_color, 1.f);

  // Ambient Lights
  vec3 ambientFinal = calcAmbient(material);

  // Diffuse Lights
  vec3 diffuseFinal = calcDiffuse(material, vs_position, vs_normal, light.position);

  // Specular Light
  vec3 specularFinal = calcSpecular(material, vs_position, vs_normal, light.position, cameraPos);

  // Attenuation

  // Final Light
  fs_color =
    //texture(material.diffuseTex, vs_texcoord) *
    vec4(vs_color * light.color, 1.f) *
    (
      // Lights
      vec4(ambientFinal, 1.f) +
      vec4(diffuseFinal, 1.f) +
      vec4(specularFinal, 1.f)
    );
}
