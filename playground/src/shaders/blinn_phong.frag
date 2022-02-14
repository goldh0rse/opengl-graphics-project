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
uniform bool showTexture;
uniform vec3 cameraPos;

void main() {
  vec3 N = normalize(vs_normal);
  vec3 L = normalize(light.position - vs_position);

  float lambertian = max(dot(N, L), 0.0);
  float specular = 0.0;
  if(lambertian > 0.0){
    vec3 R = reflect(-L, N);                      // Reflected light vector
    vec3 V = normalize(cameraPos - vs_position);  // Vector to viewer

    // Compute the specular term
    float specAngle = max(dot(R, V), 0.0);
    specular = pow(specAngle, material.alpha);
  }

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
