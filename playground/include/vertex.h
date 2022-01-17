/* vertex.h - Vertex struct.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm/glm.hpp>

struct Vertex {
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texcoord;
  glm::vec3 normal;
};
#endif
