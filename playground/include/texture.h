#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2.h>
#include "std_image.h"


using namespace std;

class Texture {
public:
  Texture(const char* fileName, GLenum type);
  ~Texture(){
    glDeleteTextures(1, &this->id);
  }

  void bind(GLint textureUnit);
  void unbind(void);

  inline GLuint getID() const { return this->id; }

private:
  GLuint id;
  int width, height, nrChannels;
  unsigned int type;
  GLint textureUnit;

};
