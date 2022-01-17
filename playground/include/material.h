/* material.h - Header file for the Material class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
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

  /* CONSTRUCTORS & DECONSTRUCTORS */
  /**
   * Material  [The main Material constructor]
   * @param ambient     [the starting ambient light property of the material]
   * @param diffuse     [the starting diffuse light property of the material]
   * @param specular    [the starting specular light property of the material]
   * @param alpha       [the starting shinyness light property of the material]
   * @param diffuseTex  [the starting diffuse texture id of the material]
   */
  Material(
    glm::vec3 ambient,
    glm::vec3 diffuse,
    glm::vec3 specular,
    GLfloat alpha,
    GLint diffuseTex
  );

  /**
   * ~Material [the class Deconstructor]
   * @note Currently not necessary
   */
  ~Material(){};

  /* METHODS */
  /**
   * sendToShader [Updates the Material uniform in the input shaders]
   * @param program  [A shader where the Material uniform is updated]
   */
  void sendToShader(Shader& program);

  /**
   * updateAmbient [Updates the ambient color property of the material]
   * @param r  [the red ambient component]
   * @param g  [the green ambient component]
   * @param b  [the blue ambient component]
   */
  void updateAmbient(float r, float g, float b);

  /**
   * updateDiffuse [Updates the diffuse color property of the material]
   * @param r  [the red diffuse component]
   * @param g  [the green diffuse component]
   * @param b  [the blue diffuse component]
   */
  void updateDiffuse(float r, float g, float b);

  /**
   * updateSpecular [Updates the specular color property of the material]
   * @param r  [the red specular component]
   * @param g  [the green specular component]
   * @param b  [the blue specular component]
   */
  void updateSpecular(float r, float g, float b);

  /**
   * updateAlpha [Updates the shinyness (alpha) of the material]
   * @param alpha  [the new shyness (alpha) value]
   */
  void updateAlpha(float alpha);

  /**
   * updateDiffuseTex [Updates the diffuse texture id of the material]
   * @param diffuseTex  [The new diffuse texture id]
   */
  void updateDiffuseTex(GLint diffuseTex);

private:
  /* ATTRIBUES */
  glm::vec3 ambient;    // The ambient color of the material
  glm::vec3 diffuse;    // The diffuse color of the material
  glm::vec3 specular;   // The specular color of the material
  float alpha;          // The shinyness (alpha) value of the material
  GLint diffuseTex;     // The diffuse texture id of the material
};


#endif
