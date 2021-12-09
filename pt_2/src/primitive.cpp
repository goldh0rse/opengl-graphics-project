#include "primitive.h"

Primitive::Primitive(){}

void Primitive::set(
  const Vertex* vertices, const unsigned nrOfVertices,
  const GLuint* indices, const unsigned nrOfIndices){
    for (size_t i = 0; i < nrOfVertices; i++) {
      this->vertices.push_back(vertices[i]);
    }

    for (size_t i = 0; i < nrOfIndices; i++) {
      this->indices.push_back(indices[i]);
    }
}
