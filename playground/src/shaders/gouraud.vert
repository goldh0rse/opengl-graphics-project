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

out vec4 color;

uniform mat4 ModelMatrix, ViewMatrix, ProjectionMatrix;
uniform bool showTexture;
uniform Light light;
uniform Material material;


void main(){
  vec4 vertPos4 = ViewMatrix * vec4(vs_position, 1.0);
  vec3 vertPos = vec3(vertPos4) / vertPos4.w;
  vec3 normalInterp = vec3(ModelMatrix * vec4(vs_normal, 0.0));
  gl_Position = ProjectionMatrix * vertPos4;

  vec3 N = normalize(vs_normal);
  vec3 L = normalize(light.position - vertPos);

  // Lambert's cosine law
  float lambertian = max(dot(N, L), 0.0);
  float specular = 0.0;
  if(lambertian > 0.0) {
    vec3 R = reflect(-L, N);      // Reflected light vector
    vec3 V = normalize(-vertPos); // Vector to viewer
    // Compute the specular term
    float specAngle = max(dot(R, V), 0.0);
    specular = pow(specAngle, material.alpha);
  }
  if (showTexture){
    color =
      texture(material.diffuseTex, vs_texcoord * -1.f) *
      vec4(vs_color * light.color, 1.f) *
      vec4(
        material.ambient * light.ambient +
        material.diffuse * lambertian +
        material.specular * specular * light.color, 1.0
      );
  } else {
    color =
      vec4(vs_color * light.color, 1.f) *
      vec4(
        material.ambient * light.ambient +
        material.diffuse * lambertian +
        material.specular * specular * light.color, 1.0
      );
  }

}
