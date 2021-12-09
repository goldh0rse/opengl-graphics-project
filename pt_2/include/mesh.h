#ifndef MESH_H_
#define MESH_H_

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vertex.h"
#include "shader.h"
#include "texture.h"
#include "material.h"
#include "primitive.h"

using namespace std;


class Mesh {
public:
  Mesh(
    Shader* shader,
    Vertex* vertices, const unsigned& nrOfVertices,
    GLuint* indices, const unsigned& nrOfIndices,
    glm::vec3 position = glm::vec3(0.f),
    glm::vec3 origin = glm::vec3(0.f),
    glm::vec3 rotation = glm::vec3(0.f),
    glm::vec3 scale = glm::vec3(1.f)
  );

  Mesh(
    Shader* shader,
    Primitive* primitive,
    glm::vec3 position = glm::vec3(0.f),
    glm::vec3 origin = glm::vec3(0.f),
    glm::vec3 rotation = glm::vec3(0.f),
    glm::vec3 scale = glm::vec3(1.f)
  );
  
  Mesh(const Mesh& obj);

  ~Mesh();

  // Accessors

  // Modifiers
  void setPosition(const glm::vec3 position);
  void setOrigin(const glm::vec3 origin);
  void setRotation(const glm::vec3 rotation);
  void setScale(const glm::vec3 scale);

  // Functions
  void move(const glm::vec3 position);
  void rotate(const glm::vec3 rotation);
  void scaleMesh(const glm::vec3 rotation);
  void update(void);
  void render(void);

private:
  Shader* shader;
  Vertex* vertices;
  GLuint* indices;
  unsigned nrOfVertices;
  unsigned nrOfIndices;

  // Buffers
  GLuint vao;
  GLuint vbo;
  GLuint ebo;

  glm::vec3 position;
  glm::vec3 origin;
  glm::vec3 rotation;
  glm::vec3 scale;

  glm::mat4 ModelMatrix;


  void initVAO(void);
  void updateModelMatrix(void);
  void updateUniforms(void);
};

#endif
