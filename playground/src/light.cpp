/* light.cpp - Method definitions for the Light class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 ambient){
  this->position = position;
  this->color = color;
  this->ambient = ambient;
}

void Light::updatePosition(float x, float y, float z){
  this->position.x = x;
  this->position.y = y;
  this->position.z = z;
}

void Light::updateColor(float r, float g, float b){
  this->color.x = r;
  this->color.y = g;
  this->color.z = b;
}

void Light::updateAmbient(float r, float g, float b){
  this->ambient.x = r;
  this->ambient.y = g;
  this->ambient.z = b;
}

void Light::sendToShader(Shader &program){
  program.setVec3f(this->position, "light.position");
  program.setVec3f(this->color, "light.color");
  program.setVec3f(this->ambient, "light.ambient");
}
