#include "texture.h"


Texture::Texture(const char* fileName, GLenum type){
  this->type = type;
  unsigned char* img = SOIL_load_image(
    fileName,
    &this->width, &this->height,
    0, SOIL_LOAD_RGBA
  );

  glGenTextures(1, &this->id);
  glBindTexture(type, this->id);

  glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);   // Magnification
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                 // Minification

  if(img){
    glTexImage2D(
      type,         0,                GL_RGBA,
      this->width,  this->height,     0,
      GL_RGBA,      GL_UNSIGNED_BYTE, img
    );
    glGenerateMipmap(type);
  } else {
    cout << "Image texture loading failed: " << fileName << endl;
    cout << SOIL_last_result() << endl;
  }

  glActiveTexture(0);
  glBindTexture(type, 0); // UNDBIND GL_TEXTURE_2D
  SOIL_free_image_data(img);
}

void
Texture::bind(const GLint textureUnit){
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(this->type, this->id);
}

void
Texture::unbind(void){
  glActiveTexture(0);
  glBindTexture(this->type, 0);
}
