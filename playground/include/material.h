#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"

using namespace std;

class Material {
public:
  Material(
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular,
    GLfloat alpha,
    GLint diffuseTex
  );
  ~Material(){};

  void sendToShader(Shader& program);
  void updateAmbient(float r, float g, float b);
  void updateDiffuse(float r, float g, float b);
  void updateSpecular(float r, float g, float b);
  void updateAlpha(float alpha);

private:
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float alpha;
  GLint diffuseTex;
};


#endif
