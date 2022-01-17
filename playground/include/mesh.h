/* mesh.h - Header file for the Mesh class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */

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
  /* CONSTRUCTORS & DECONSTRUCTOR */
  /**
   * Mesh [Constructor of the Mesh class]
   * @param shader        [The shader that draws the Vertices]
   * @param vertices      [The vertices defining the mesh]
   * @param nrOfVertices  [The total number of vertices in the mesh]
   * @param indices       [The indices that identify the vertex positions]
   * @param nrOfIndices   [The total number of indices]
   * @param position      [The world space origin of the object]
   */
  Mesh(
    Shader* shader,
    Vertex* vertices, const unsigned& nrOfVertices,
    GLuint* indices, const unsigned& nrOfIndices,
    glm::vec3 position = glm::vec3(0.f),
    glm::vec3 origin = glm::vec3(0.f),
    glm::vec3 rotation = glm::vec3(0.f),
    glm::vec3 scale = glm::vec3(1.f)
  );

  /**
   * Mesh [Constructor of the Mesh class]
   * @param shader     [The shader that draws the Vertices]
   * @param primitive  [The primitive class defining the mesh]
   * @param position   [The world space origin of the object]
   */
  Mesh(
    Shader* shader,
    Primitive* primitive,
    glm::vec3 position = glm::vec3(0.f),
    glm::vec3 origin = glm::vec3(0.f),
    glm::vec3 rotation = glm::vec3(0.f),
    glm::vec3 scale = glm::vec3(1.f)
  );

  /**
   * Mesh [Constructor / Cloner of a mesh object]
   * @param obj  [A mesh object to be cloned]
   */
  Mesh(const Mesh& obj);

  /**
   * ~Mesh [The deconstuctor of the class]
   */
  ~Mesh();

  /* METHODS */
  /**
   * setPosition [A setter method that sets the position attribute]
   * @param position  [the new position attribute]
   */
  inline void setPosition(const glm::vec3 position){ this->position = position; }
  /**
   * setOrigin [A setter method that sets the origin attribute]
   * @param origin [the new origin attribute]
   */
  inline void setOrigin(const glm::vec3 origin){ this->origin = origin; }

  /**
   * setRotation [A setter method that sets the rotation attribute]
   * @param rotation  [the new rotation attribute]
   */
  inline void setRotation(const glm::vec3 rotation){ this->rotation = rotation; }

  /**
   * setScale [A setter method that sets the scale attribute]
   * @param scale  [the new scale attribute]
   */
  inline void setScale(const glm::vec3 scale){ this->scale = scale; }

  /**
   * move [Moves the position of the mesh the distance of the parameter vector]
   * @param position  [The distance the mesh should be moved]
   */
  void move(const glm::vec3 position);

  /**
   * rotate [Rotates the mesh in accordance to the radians produces by the
   *         parameter vector when updating the ModelMatrix]
   * @param rotation  [The rotation vector]
   */
  void rotate(const glm::vec3 rotation);

  /**
   * scaleMesh [Scales the the mesh in accordance to the input scalar vector]
   * @param rotation  [The scalar vector]
   */
  void scaleMesh(const glm::vec3 scalar);

  /**
   * render [Render the mesh]
   */
  void render(void);

private:

  /**
   * initBuffers [initialises the buffers of the mesh]
   */
  void initBuffers(void);

  /**
   * updateModelMatrix [Updates the ModelMatrix with the rotation,
   *                    rotation & scaler vectors]
   */
  void updateModelMatrix(void);

  /**
   * updateUniforms [Updates the ModelMatrix uniform in the shader]
   */
  void updateUniforms(void);

  /* ATTRIBUTES */
  Shader* shader;         // The shader that is used to draw the mesh
  Vertex* vertices;       // The vertices of the mesh
  GLuint* indices;        // The indices of the vertices
  unsigned nrOfVertices;  // The total number of vertices of the mesh
  unsigned nrOfIndices;   // The total number of indices

  GLuint vao;             // The VAO buffer of the mesh
  GLuint vbo;             // The VBO buffer of the mesh
  GLuint ebo;             // The EBO buffer of the mesh

  glm::vec3 position;     // The current position of the mesh in the world
  glm::vec3 origin;       // The origin position of the mesh in the world
  glm::vec3 rotation;     // The rotation value of the mesh
  glm::vec3 scale;        // The scaler value of the mesh

  glm::mat4 ModelMatrix;  // The ModelMatrix that does all the transformations

};

#endif
