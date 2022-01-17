/* primitive.cpp - Method definitions for the Primitive class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */

#include "primitive.h"

Primitive::Primitive(void){}

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
