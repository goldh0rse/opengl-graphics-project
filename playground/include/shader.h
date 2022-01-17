/* shader.h - Header file for the Shader Class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader {
public:
  /* CONSTRUCTORS & DECONSTRUCTORS */
  /**
   * Shader [The class constructor]
   * @param vertexFile    [The file path to the vertex shader]
   * @param fragmentFile  [The file path to the fragment shader]
   * @param geometryFile  [The file path to the geometry shader]
   */
  Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);

  /**
   * ~Shader [The class deconstructor]
   */
  ~Shader(void){
    glDeleteProgram(this->id);
  }

  /* METHODS */
  /**
   * use  [Activates the shader]
   */
  void use(void);

  /**
   * unuse [Deactivates the shader]
   */
  void unuse(void);

  /**
   * getAttributeLocation [Fetches an attribute location for a shader uniform]
   * @param  name         [The name of the uniform attribute]
   * @return GLuint       [the uniform attribute id]
   */
  GLuint getAttributeLocation(const char* name);

  /**
   * setVec1f [A setter for uniform attribute vector containing a single float]
   * @param value  [The new value]
   * @param name   [The name of the uniform attribute]
   */
  void setVec1f(GLfloat value, const GLchar* name);

  /**
   * setVec2f [A setter for uniform attribute of a vector containing 2 floats]
   * @param value  [The new values]
   * @param name   [The name of the uniform attribute]
   */
  void setVec2f(glm::fvec2 value, const GLchar* name);

  /**
   * setVec3f [A setter for uniform attribute of a vector containing 3 floats]
   * @param value  [The new values]
   * @param name   [The name of the uniform attribute]
   */
  void setVec3f(glm::fvec3 value, const GLchar* name);

  /**
   * setMat3fv [A setter for uniform attribute of a 3x3 matrix of floats]
   * @param value     [The new matrix]
   * @param name      [The name of the uniform attribute]
   * @param transpose [A boolean that sets if the matrix should be transposed]
   */
  void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose=GL_FALSE);

  /**
   * setMat4fv [A setter for uniform attribute of a 4x4 matrix of floats]
   * @param value     [The new matrix]
   * @param name      [The name of the uniform attribute]
   * @param transpose [A boolean that sets if the matrix should be transposed]
   */
  void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose=GL_FALSE);

  /**
   * set1i [A setter for uniform attribute of a single integer / boolean]
   * @param value  [The new value]
   * @param name   [The name of the uniform attribute]
   */
  void set1i(GLint value, const GLchar* name);

  /**
   * set1f [A setter for uniform attribute of a single float]
   * @param value  [The new value]
   * @param name   [The name of the uniform attribute]
   */
  void set1f(GLfloat value, const GLchar* name);

private:

  /**
   * loadShaderSource [Loads a shader from a source file]
   * @param  fileName [The shader file path]
   * @return          [The found path of the shader]
   */
  string loadShaderSource(const char* fileName);

  /**
   * loadShader [Loads a shader defines a type]
   * @param  type      [The type of shader to be loaded (v/g/f)]
   * @param  fileName  [The filename of the shader source]
   * @return           [The identifier of the shader]
   */
  GLuint loadShader(GLenum type, const char* fileName);

  /**
   * linkProgram [Links shaders together in the pipeline]
   * @param vertexShader    [The vertex shader to be used]
   * @param GeometryShader  [The geometry shader to be used (OPTIONAL)]
   * @param fragmentShader  [The fragment shader to be used]
   */
  void linkProgram(GLuint vertexShader, GLuint GeometryShader, GLuint fragmentShader);

 /* Attributes */
  GLuint id;  // The ID of the shader

};

#endif
