#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm/glm.hpp>

// For objectloading
struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texcoord;
  glm::vec3 normal;
};
#endif
