#include "material.h"

Material::Material(
  glm::vec3 ambient,
  glm::vec3 diffuse,
  glm::vec3 specular,
  GLfloat alpha,
  GLint diffuseTex){
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->alpha = alpha;
    this->diffuseTex = diffuseTex;
}

void Material::sendToShader(Shader& program){
  program.setVec3f(this->ambient, "material.ambient");
  program.setVec3f(this->diffuse, "material.diffuse");
  program.setVec3f(this->specular, "material.specular");
  program.set1f(this->alpha, "material.alpha");
  program.set1i(this->diffuseTex, "material.diffuseTex");
}

void Material::updateAmbient(float r, float g, float b){
  this->ambient.x = r;
  this->ambient.y = g;
  this->ambient.z = b;
}

void Material::updateDiffuse(float r, float g, float b){
  this->diffuse.x = r;
  this->diffuse.y = g;
  this->diffuse.z = b;
}

void Material::updateSpecular(float r, float g, float b){
  this->specular.x = r;
  this->specular.y = g;
  this->specular.z = b;
}

void Material::updateAlpha(float alpha){
  this->alpha = alpha;
}
