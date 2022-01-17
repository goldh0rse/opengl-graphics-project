/* texture.cpp - Method definitions for the Texture class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */

#include "texture.h"


Texture::Texture(const char* fileName, GLenum type){
  this->type = type;

  glGenTextures(1, &this->id);
  glBindTexture(type, this->id);

  glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // Magnification
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // Minification


  unsigned char *img = stbi_load(
    fileName,
    &this->width, &this->height, &this->nrChannels,
    0
  );


  if(img){
    glTexImage2D(
      type,
      0,                 GL_RGBA,
      this->width,  this->height,
      0,                 GL_RGBA,
      GL_UNSIGNED_BYTE,
      img
    );
    glGenerateMipmap(type);
  } else {
    cout << "Image texture loading failed: " << fileName << endl;
  }

  glActiveTexture(0);
  glBindTexture(type, 0); // UNDBIND GL_TEXTURE_2D
  stbi_image_free(img);
}

void Texture::bind(const GLint textureUnit){
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(this->type, this->id);
}

void Texture::unbind(void){
  glActiveTexture(0);
  glBindTexture(this->type, 0);
}
