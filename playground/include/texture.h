/* texture.h - Header file for the Texture Class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "std_image.h"


using namespace std;

class Texture {
public:
  /* CONSTRUCTORS & DECONSTRUCTORS */
  /**
   * Texture [The class constructor]
   * @param fileName  [The file path of the texture image]
   * @param type      [The texture type (2D / 3D, etc)]
   */
  Texture(const char* fileName, GLenum type);

  /**
   * ~Texture [The class deconstructor]
   */
  ~Texture(void){
    glDeleteTextures(1, &this->id);
  }

  /* METODS */
  /**
   * bind [Activates the texture]
   * @param textureUnit  [The id of the texture]
   */
  void bind(GLint textureUnit);

  /**
   * unbind [Deactivates the texture]
   */
  void unbind(void);

  /**
   * getID [A getter for the id attribute of the texture]
   * @return GLuint [The id attribute]
   */
  inline GLuint getID(void) const { return this->id; }

private:
  /* ATTRIBUTES */
  GLuint id;                      // The id of the texture
  int width, height, nrChannels;  // Image width, Height & nr of channels
  unsigned int type;              // The type of the texture (2D / 3D / etc..)

};
#endif
