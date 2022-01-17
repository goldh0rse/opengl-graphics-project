/* mesh.cpp - Method definitions for the Mesh class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */

#include "mesh.h"

Mesh::Mesh(
  Shader* shader,
  Vertex* vertices, const unsigned& nrOfVertices,
  GLuint* indices, const unsigned& nrOfIndices,
  glm::vec3 position,
  glm::vec3 origin,
  glm::vec3 rotation,
  glm::vec3 scale){

    this->shader = shader;
    this->position = position;
    this->origin = origin;
    this->rotation = rotation;
    this->scale = scale;
    this->nrOfVertices = nrOfVertices;
    this->nrOfIndices = nrOfIndices;

    this->vertices = new Vertex[this->nrOfVertices];
    for (size_t i = 0; i < this->nrOfVertices; i++){
      this->vertices[i] = vertices[i];
    }

    this->indices = new GLuint[this->nrOfIndices];
    for (size_t i = 0; i < this->nrOfIndices; i++){
      this->indices[i] = indices[i];
    }


    this->initBuffers();
    this->updateModelMatrix();
};

Mesh::Mesh(
  Shader* shader,
  Primitive* primitive,
  glm::vec3 position,
  glm::vec3 origin,
  glm::vec3 rotation,
  glm::vec3 scale){
    this->shader = shader;
    this->position = position;
    this->origin = origin;
    this->rotation = rotation;
    this->scale = scale;
    this->nrOfVertices = primitive->getNrOfVertices();
    this->nrOfIndices = primitive->getNrOfIndices();

    this->vertices = new Vertex[this->nrOfVertices];
    for (size_t i = 0; i < this->nrOfVertices; i++){
      this->vertices[i] = primitive->getVertices()[i];
    }

    this->indices = new GLuint[this->nrOfIndices];
    for (size_t i = 0; i < this->nrOfIndices; i++){
      this->indices[i] = primitive->getIndices()[i];
    }

    this->initBuffers();
    this->updateModelMatrix();
};

Mesh::Mesh(const Mesh& obj){
  this->shader = obj.shader;
  this->position = obj.position;
  this->origin = obj.origin;
  this->rotation = obj.rotation;
  this->scale = obj.scale;
  this->nrOfVertices = obj.nrOfVertices;
  this->nrOfIndices = obj.nrOfIndices;

  this->vertices = new Vertex[this->nrOfVertices];
  for (size_t i = 0; i < this->nrOfVertices; i++){
    this->vertices[i] = obj.vertices[i];
  }

  this->indices = new GLuint[this->nrOfIndices];
  for (size_t i = 0; i < this->nrOfIndices; i++){
    this->indices[i] = obj.indices[i];
  }

  this->initBuffers();
  this->updateModelMatrix();
}

Mesh::~Mesh(){
  glDeleteVertexArrays(1, &this->vao);
  glDeleteBuffers(1, &this->vbo);

  if (this->nrOfIndices > 0){
    glDeleteBuffers(1, &this->ebo);
  }

  delete[] this->vertices;
  delete[] this->indices;
}

void Mesh::render(void){
  this->updateModelMatrix();
  this->updateUniforms();

  this->shader->use();

  glBindVertexArray(this->vao);

  if(this->nrOfIndices == 0){
    glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
  } else {
    glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
  }
  this->shader->unuse();

  glBindVertexArray(0);
  glUseProgram(0);
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::move(const glm::vec3 position){
  this->position += position;
}

void Mesh::rotate(const glm::vec3 rotation){
  this->rotation += rotation;
}

void Mesh::scaleMesh(const glm::vec3 scalar){
  this->scale += scalar;
}

void Mesh::initBuffers(void){
  // GEN & BIND VAO
  glCreateVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao); // "Putting our box infront of us"

  // GEN & BIND VBO + SEND DATA
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), this->vertices, GL_STATIC_DRAW);

  // GEN & BIND EBO + SEND DATA
  if(this->nrOfIndices > 0){
    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), this->indices, GL_STATIC_DRAW);
  }

  // Set VertexAttribPointers & Enable (INPUT ASSEMBLY)
  // POSITION
  GLuint attribLoc = this->shader->getAttributeLocation("vertex_position");
  glVertexAttribPointer(
    attribLoc,                            // attribute.
    3,                                    // size
    GL_FLOAT,                             // type
    GL_FALSE,                             // normalize?
    sizeof(Vertex),                       // stride
    (GLvoid*)offsetof(Vertex, position)   // array buffer offset
  ); // Layout 0 (position)
  glEnableVertexAttribArray(attribLoc);

  // COLOR
  attribLoc = this->shader->getAttributeLocation("vertex_color");
  glVertexAttribPointer(
    attribLoc,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (GLvoid*)offsetof(Vertex, color)
  ); // Layout 1 (color)
  glEnableVertexAttribArray(attribLoc);

  // TEXCOORD
  attribLoc = this->shader->getAttributeLocation("vertex_texcoord");
  glVertexAttribPointer(
    attribLoc,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (GLvoid*)offsetof(Vertex, texcoord)
  ); // Layout 2 (texture coordinate)
  glEnableVertexAttribArray(attribLoc);

  // NORMALS
  attribLoc = this->shader->getAttributeLocation("vertex_normal");
  glVertexAttribPointer(
    attribLoc,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (GLvoid*)offsetof(Vertex, normal)
  ); // Layout 3(Color)
  glEnableVertexAttribArray(attribLoc);

  // UNBIND
  glBindVertexArray(0);
}

void Mesh::updateModelMatrix(void){
  this->ModelMatrix = glm::mat4(1.f);
  this->ModelMatrix = glm::translate(this->ModelMatrix, this->origin);
  this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
  this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
  this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
  this->ModelMatrix = glm::translate(this->ModelMatrix, this->position - this->origin);
  this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

void Mesh::updateUniforms(void){
  this->shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
}
