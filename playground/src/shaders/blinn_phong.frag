#version 430

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float alpha;
  sampler2D diffuseTex;
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
uniform vec3 cameraPos;
uniform bool showTexture;


// Functions
vec3 calcAmbient(Material material){
  return material.ambient * light.ambient;
}

vec3 calcDiffuse(Material material, vec3 position, vec3 normal, vec3 lightPos){
  vec3 posToLightDirVec = normalize(lightPos - position);
  float diffuse = clamp(dot(posToLightDirVec, normal), 0, 1);
  return  material.diffuse * diffuse;
}

vec3 calcSpecular(Material material, vec3 position, vec3 normal, Light light, vec3 cameraPos){
  vec3 lightToPosDirVec = normalize(position - light.position);
  vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(normal)));
  vec3 posToViewDirVec = normalize(cameraPos - position);
  float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), material.alpha);
  return material.specular * specularConstant;
}

void main() {
  // Ambient Lights
  // vec3 ambientFinal = calcAmbient(material);

  // Diffuse Lights
  // vec3 diffuseFinal = calcDiffuse(material, vs_position, vs_normal, light.position);


  vec3 N = normalize(vs_normal);
  vec3 L = normalize(light.position - vs_position);

  float lambertian = max(dot(N, L), 0.0);
  float specular = 0.0;
  if(lambertian > 0.0){
    vec3 R = reflect(-L, N);              // Reflected light vector
    vec3 V = normalize(-vs_position); // Vector to viewer
    // Compute the specular term
    float specAngle = max(dot(R, V), 0.0);
    specular = pow(specAngle, material.alpha);
  }

  // fs_color = vec4(
  //   material.ambient * light.ambient +
  //   material.diffuse * lambertian +
  //   material.specular * specular * light.color, 1.0
  // );

  // Specular Light
  // vec3 specularFinal = calcSpecular(material, vs_position, vs_normal, light, cameraPos);

  // Attenuation

  // Final Light
  if (showTexture){
    fs_color =
      texture(material.diffuseTex, vs_texcoord * -1.f) *
      vec4(
        material.ambient * light.ambient +
        material.diffuse * lambertian +
        material.specular * specular * light.color, 1.0
      );
  } else {
    fs_color =
      vec4(vs_color * light.color, 1.f) *
      vec4(
        material.ambient * light.ambient +
        material.diffuse * lambertian +
        material.specular * specular * light.color, 1.0
      );
  }

}
