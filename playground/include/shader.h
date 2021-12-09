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
  Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);
  ~Shader(){
    glDeleteProgram(this->id);
  }

  void use();
  void unuse();

  GLuint getAttributeLocation(const char* name);

  void setVec1f(GLfloat value, const GLchar* name);
  void setVec2f(glm::fvec2 value, const GLchar* name);
  void setVec3f(glm::fvec3 value, const GLchar* name);
  void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose=GL_FALSE);
  void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose=GL_FALSE);
  void set1i(GLint value, const GLchar* name);

private:
  GLuint id;

  std::string loadShaderSource(const char* fileName);
  GLuint loadShader(GLenum type, const char* fileName);
  void linkProgram(GLuint vertexShader, GLuint GeometryShader, GLuint fragmentShader);


};

#endif
