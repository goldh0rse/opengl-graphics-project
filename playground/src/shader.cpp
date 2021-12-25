#include "shader.h"

// Public
Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile){
  GLuint vShader = 0;
  GLuint fShader = 0;
  GLuint gShader = 0;

  vShader = loadShader(GL_VERTEX_SHADER, vertexFile);

  if(strcmp(geometryFile, "") != 0){
    gShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
  }
  fShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

  this->linkProgram(vShader, fShader, gShader);

}

void Shader::use(void){
  glUseProgram(this->id);
}

void Shader::unuse(void){
  glUseProgram(0);
}

GLuint Shader::getAttributeLocation(const char* name){
  return glGetAttribLocation(this->id, name);
}

void Shader::setVec1f(GLfloat value, const GLchar* name){
  this->use();
  glUniform1f(glGetUniformLocation(this->id, name), value);
  this->unuse();
}

void Shader::setVec2f(glm::fvec2 value, const GLchar* name){
  this->use();
  glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
  this->unuse();
}

void Shader::setVec3f(glm::fvec3 value, const GLchar* name){
  this->use();
  glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
  this->unuse();
}

void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose){
  this->use();
  glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
  this->unuse();
}

void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose){
  this->use();
  glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
  this->unuse();
}

void Shader::set1i(GLint value, const GLchar* name){
  this->use();
  glUniform1i(glGetUniformLocation(this->id, name), value);
  this->unuse();
}

void Shader::set1f(GLfloat value, const GLchar* name){
  this->use();
  glUniform1f(glGetUniformLocation(this->id, name), value);
  this->unuse();
}

// Private
string Shader::loadShaderSource(const char* fileName){
  string temp = "";
  string src = "";

  ifstream in_file;

  //load vertex shader file
  in_file.open(fileName);
  if(in_file.is_open()){
    while(std::getline(in_file, temp)){
      src += temp + "\n";
    }
  } else {
      cerr << "Failed to read shaderfile: " << fileName << endl;
  }
  in_file.close();
  return src;
}

GLuint Shader::loadShader(GLenum type, const char* fileName){
  GLuint shader = glCreateShader(type);
  string str_src = this->loadShaderSource(fileName);
  const GLchar* shaderSrc = str_src.c_str();
  glShaderSource(shader, 1, &shaderSrc, NULL);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success){
    GLint  logSize;

    cerr << "Failed to compile shader: " << fileName << endl;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    if (logSize > 0) {
        char logMsg[logSize+1];
        glGetShaderInfoLog(shader, logSize, NULL, &(logMsg[0]));
        cerr << "Shader info log: " << logMsg << endl;
    }
  }
  return shader;
}

void Shader::linkProgram(
  GLuint vertexShader,
  GLuint fragmentShader,
  GLuint geometryShader){

  GLint success;
  this->id = glCreateProgram();

  glAttachShader(this->id, vertexShader);
  if(geometryShader){
    glAttachShader(this->id, geometryShader);
  }
  glAttachShader(this->id, fragmentShader);

  glLinkProgram(this->id);

  glGetProgramiv(this->id, GL_LINK_STATUS, &success);
  if (!success) {
    GLint  logSize;

    cerr << "Shader program failed to link shaders!" << endl;

    glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &logSize);
    if (logSize > 0) {
      char logMsg[logSize+1];
      glGetProgramInfoLog(this->id, logSize, NULL, &(logMsg[0]));
      cerr << "Program info log: " << logMsg << endl;
      free(logMsg);
    }
  }

  // End
  glUseProgram(0);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

}
